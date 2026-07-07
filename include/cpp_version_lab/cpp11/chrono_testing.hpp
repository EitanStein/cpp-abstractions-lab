#pragma once
#include <chrono>
#include <print>
#include <thread>

// many additions were made in C++20

void chrono_testing(){
    {
        constexpr bool is_steady = std::is_same_v<std::chrono::high_resolution_clock, std::chrono::steady_clock>;
        constexpr bool is_system = std::is_same_v<std::chrono::high_resolution_clock, std::chrono::system_clock>;

        if(is_system)
            std::println("high resolution clock is the same as system clock which can go back/forward int time due to sync");
        if(is_steady)
            std::println("high resolution clock is the same as steady clock which can only go forward in fixed intervals");
        auto now_system = std::chrono::system_clock::now();
        auto now_steady = std::chrono::steady_clock::now();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        auto later_system = std::chrono::system_clock::now(); // system is better
        auto later_steady = std::chrono::steady_clock::now();
        std::println("diff system : {}ns", (later_system - now_system).count());
        std::println("diff steady : {}ns", (later_steady - now_steady).count());
        
    }
}