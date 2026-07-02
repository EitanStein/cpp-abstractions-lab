#pragma once

struct NoExplicit{
    NoExplicit(int) {}
    NoExplicit(int, int) {}
    operator bool() const { return true;}
};

struct Explicit{
    explicit Explicit(int) {}
    explicit Explicit(int, int) {}
    explicit operator bool() const { return true;}
};

void explicit_lab(){
    NoExplicit a1(1);
    NoExplicit a2(1, 1);
    NoExplicit a3 = 1;
    NoExplicit a4 = {1, 1};
    if(a4) {}
    bool b1 = a4;

    Explicit c1(1);
    Explicit c2(1, 1);
    // Explicit c3 = 1; // has to explicitly call Explicit(int) constructor
    // Explicit c4 = {1, 1}; // has to explicitly call Explicit(int, int) constructor
    if(c2) {} // calls bool func
    // bool b2 = c2; // doesnt call bool func
    bool b2 = static_cast<bool>(c2); // calls bool func
}