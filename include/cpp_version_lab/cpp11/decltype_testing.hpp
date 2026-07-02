#pragma once

#include "utils/helper_funcs.hpp"


// cpp 14 doesnt require that trailing type anymore
// instead it does decltype(auto)
// if it was just auto it would strip ref and const
// one danger of returning decltype(auto) is that return x; will return in while return (x); returns int&
template<typename T, typename U>
auto func(T t, U u) -> decltype(t + u){
    return t+u;
}

// decltype(x) -> x's exact type
// decltype((x)) -> x's value category
void decltype_demo(){
    std::println("Testing decltype:");
    int x = 5;
    
    print_type<decltype(x)>();     // int
    print_type<decltype((x))>();   // int& - lvalue
    print_type<decltype(((x)))>(); // int&

    print_type<decltype(func(1, 2.0))>(); // double

    int y = 7;
    
    print_type<decltype(x+y)>();   // int
    print_type<decltype((x+y))>(); // int - prvalue
    print_type<decltype((x)+y)>(); // int

    print_type<decltype(5)>();  // int
    print_type<decltype((5))>();// int - prvalue
    print_type<decltype(std::move(x))>(); // int&& - type after move is int&&
    print_type<decltype((std::move(x)))>(); // int&& - rvalue
}


