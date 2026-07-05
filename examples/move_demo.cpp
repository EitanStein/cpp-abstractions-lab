#include "cpp_abstractions_lab/move.hpp"
#include "utils/lifetime.hpp"
#include <utility>
#include <print>

int main(){
    Lifetime l1;
    Lifetime l2 = my_move(l1); // call move properly
    Lifetime l3{my_move(l2)}; // call move properly
    Lifetime l4{my_move(Lifetime{})}; // call move properly

    const Lifetime l5;
    const Lifetime l6{my_move(l5)}; // call copy since its a const


    Lifetime lvalue;
    const Lifetime c_lvalue;

    // lvalue
    static_assert(std::is_same_v<decltype(my_move(lvalue)), Lifetime&&>);
    static_assert(std::is_same_v<decltype(my_move(lvalue)), decltype(std::move(lvalue))>);
    // const lvalue
    static_assert(std::is_same_v<decltype(my_move(c_lvalue)), const Lifetime&&>);
    static_assert(std::is_same_v<decltype(my_move(c_lvalue)), decltype(std::move(c_lvalue))>);
    // rvalue
    static_assert(std::is_same_v<decltype(my_move(Lifetime{})), Lifetime&&>);
    static_assert(std::is_same_v<decltype(my_move(Lifetime{})), decltype(std::move(Lifetime{}))>);
}