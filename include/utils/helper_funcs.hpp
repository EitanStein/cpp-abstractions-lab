#pragma once

#include <string_view>
#include <print>

template<typename T>
inline void print_type(){
    #if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
        std::string_view name = __PRETTY_FUNCTION__;
        size_t start = name.find("T = ") + 4;
        size_t end = name.find("]");
        println("{}", name.substr(start, end-start));
    #elif defined(__MSVC__)
        std::string_view name = __FUNCSIG__;
        size_t start = name.find("<") + 4;
        size_t end = name.find(">(");
        println("{}", name.substr(start, end-start));
    #endif
}