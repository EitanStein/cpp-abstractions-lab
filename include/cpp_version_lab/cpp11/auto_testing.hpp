#pragma once
#include <print>
#include <vector>
#include <string>
#include <string_view>

template<typename T>
void print_type(){
    std::string_view name = __PRETTY_FUNCTION__;
    size_t start = name.find("T = ") + 4;
    size_t end = name.find("]");
    println("{}", name.substr(start, end-start));
}

void testing_auto_deduction(){
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

    // std::vector<auto> x{1,2,3} - compile error can't use auto inside <> 
}

// fails in C++11 without trailing return type
auto func(int x) -> int{
    return x;
}