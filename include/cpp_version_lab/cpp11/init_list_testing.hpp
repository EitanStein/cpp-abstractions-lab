#pragma once
#include "utils/lifetime.hpp"
#include <initializer_list>
#include <vector>
#include <array>

struct MyStruct {
    int x{};
    MyStruct(std::initializer_list<Lifetime> init_list) { // no copy made
        for (auto& num : init_list)
            x += 1;
    }
    MyStruct(const std::vector<Lifetime>& init_list) { // need ref for no copy and sits on the heap
        for (auto& num : init_list)
            x += 1;
    }
    MyStruct(const std::array<Lifetime, 3>& init_list) { // need to know size at compile time
        for (auto& num : init_list)
            x += 1;
    }
};


void initialization_list_demo(){
    std::println("\nInitialization list demo:");
    {
        std::initializer_list<Lifetime> init_list {{},{},{}}; // 3 ctors here

        MyStruct s(init_list); // no copy made
    }
}

