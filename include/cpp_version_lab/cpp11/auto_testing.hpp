#pragma once

#include "utils/helper_funcs.hpp"
#include <vector>


void testing_auto_deduction(){
    std::println("\nTesting auto:");
    {
        auto x = 5;
        print_type<decltype(x)>();   // int
    }
    {
        auto x = 5.0;
        print_type<decltype(x)>(); // double
    }
    {
        auto x = 5.0f;
        print_type<decltype(x)>(); // float
    }
    {
        auto x = true;
        print_type<decltype(x)>(); // bool
    }
    {
        auto x = 0;
        print_type<decltype(x)>(); // int
    }
    {
        auto x = std::vector<int>{1,2,3};
        print_type<decltype(x)>(); // std::vector<int>
    }
    {
        auto x = std::vector<double>{1,2,3};
        print_type<decltype(x)>(); // std::vector<double>
    }
    {
        auto x = [](int x){return "my lambda";};
        print_type<decltype(x)>();      // testing_auto_deduction()::<lambda(int)>
    }
    {
        int x = 5;
        const int& y = x;
        auto z = y;

        auto a = [&x]()->const int&{return x;}();

        print_type<decltype(x)>(); // int
        print_type<decltype(y)>(); // const int&
        // auto strips const and ref
        print_type<decltype(z)>(); // int
        print_type<decltype(a)>(); // int
    }

    // std::vector<auto> x{1,2,3} - compile error can't use auto inside <> 
}

// fails in C++11 without trailing return type
auto func(int x) -> int{
    return x;
}