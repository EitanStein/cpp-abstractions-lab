#pragma once

#include <print>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

namespace SyncTestingNSpace{
struct UniqueLockStruct{
    int val{};
    std::mutex m;

    void operator++(){
        std::unique_lock<std::mutex> lock(m);
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
        std::lock_guard<std::mutex> lock(m);
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

void sync_testing(){
    std::println("\nthreading tests:");
    {
    SyncTestingNSpace::UniqueLockStruct x;
    std::vector<std::thread> thread_vec;

    auto start = std::chrono::steady_clock::now();
    for(int i=0; i<5;++i){
        thread_vec.emplace_back([&x](){SyncTestingNSpace::incrementLotsUnique(x);});
    }

    for(auto& th : thread_vec)
        th.join();
    auto end = std::chrono::steady_clock::now();
    std::println("{}, took {} time", x.val, (end - start).count());
    }

    {
    SyncTestingNSpace::GuardLockStruct x;
    std::vector<std::thread> thread_vec;

    auto start = std::chrono::steady_clock::now();
    for(int i=0; i<5;++i){
        thread_vec.emplace_back([&x](){SyncTestingNSpace::incrementLotsGuard(x);});
    }

    for(auto& th : thread_vec)
        th.join();
    auto end = std::chrono::steady_clock::now();
    std::println("{}, took {} time", x.val, (end - start).count());
    }
}