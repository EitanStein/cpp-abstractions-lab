#pragma once

#include <print>

struct Lifetime{
    Lifetime() {std::println("ctor");}
    Lifetime(const Lifetime&) {std::println("copy ctor");}
    Lifetime(Lifetime&&) noexcept {std::println("move ctor");}
    Lifetime& operator=(const Lifetime&) {std::println("copy operator"); return *this;}
    Lifetime& operator=(Lifetime&&) noexcept {std::println("move operator"); return *this;}
    ~Lifetime() {std::println("dtor");}
};