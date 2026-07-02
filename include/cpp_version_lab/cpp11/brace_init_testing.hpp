#pragma once

#include "utils/helper_funcs.hpp"
#include "utils/lifetime.hpp"
#include <cassert>

void brace_init_demo(){
    std::println("\nbrace initialization demo:");

    int x{3};
    // int y{3.5}; compile error
    std::pair<int, double> z{1, 3.0};

    struct MyStruct : public Lifetime{
        int x;
        std::pair<int, double> y;
    };

    // MyStruct s1{{}, 1,1,1.0}; compile error
    MyStruct s2{{}, 1,{1,1.0}}; // need empty ctor for lifetime - single ctor call

    MyStruct s3{}; // single ctor call

    struct MoreOuterStruct : public MyStruct{
        int outer;
    };

    MoreOuterStruct s4{}; // single ctor call
    MoreOuterStruct s5{{{}, 1, {1,1.0}}, 3}; // single ctor call but complex brace initialization (C++20 adds designated initilaization but wont be useful in this example till C++23)
    assert(s5.outer == 3);
}