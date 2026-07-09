#pragma once

#include <print>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <atomic>

namespace MutexNLocks{
struct UniqueLockStruct{
    int val{};
    std::mutex m;

    void operator++(){
        std::unique_lock<std::mutex> lock(m); // can defer lock to not 'actually' lock right now
        // can lock/unlock whenever it needs
        ++val;
    }

    void operator--(){
        std::unique_lock<std::mutex> lock(m);
        --val;
    }
};

struct GuardLockStruct{
    int val{};
    std::mutex m;

    void operator++(){
        std::lock_guard<std::mutex> lock(m); // locks now and unlocks on destrcution
        // cant be used for condition variable
        ++val;
    }

    void operator--(){
        std::lock_guard<std::mutex> lock(m);
        --val;
    }
};

void incrementLotsUnique(UniqueLockStruct& val){
    for(int _ = 0 ; _ < 10'000 ; ++_){
        ++val;
    }
}

void incrementLotsGuard(GuardLockStruct& val){
    for(int _ = 0 ; _ < 10'000 ; ++_){
        ++val;
    }
}
}

namespace AtomicsTesting{
struct MyStruct{
    std::atomic<bool> ready{};
    int x{};

    void change_x(){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        x = 42;
        // ready.store(true, std::memory_order_relaxed); // might reorder the commands so x=0 after storing true - this causes data race error in TSan
        ready.store(true, std::memory_order_release);
    }

    void print_x(){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        // while(!ready.load(std::memory_order_relaxed)) {} // might still use a pre loaded x rather than a re-flushed value
        while(!ready.load(std::memory_order_acquire)) {}
        std::println("flag was true and x is {}", x);
    }
};



}

void sync_testing(){
    std::println("\nthreading tests:");
    {
    MutexNLocks::UniqueLockStruct x;
    std::vector<std::thread> thread_vec;

    auto start = std::chrono::steady_clock::now();
    for(int i=0; i<5;++i){
        thread_vec.emplace_back([&x](){MutexNLocks::incrementLotsUnique(x);});
    }

    for(auto& th : thread_vec)
        th.join(); // C++20 has jthreads that do not require join
    auto end = std::chrono::steady_clock::now();
    std::println("{}, took {} time", x.val, (end - start).count());
    }

    {
    MutexNLocks::GuardLockStruct x;
    std::vector<std::thread> thread_vec;

    auto start = std::chrono::steady_clock::now();
    for(int i=0; i<5;++i){
        thread_vec.emplace_back([&x](){MutexNLocks::incrementLotsGuard(x);});
    }

    for(auto& th : thread_vec)
        th.join();
    auto end = std::chrono::steady_clock::now();
    std::println("{}, took {} time", x.val, (end - start).count());
    }

    {
    AtomicsTesting::MyStruct x;
    std::thread t1([&x]{x.print_x();});
    std::thread t2([&x]{x.change_x();});

    t1.join();
    t2.join();
    }
}