#pragma once

struct NoExplicit{
    NoExplicit(){};
    NoExplicit(int) {}
    NoExplicit(int, int) {}
    operator bool() const { return true;}
};

struct NoExplicitMultipleVals{
    NoExplicitMultipleVals(bool, int y =5, double=7.0, bool =false) {}
    operator bool() const { return true;}
};

struct NoExplicitMultipleVals2{
    NoExplicitMultipleVals2(bool, int, double=7.0, bool =false) {}
    operator bool() const { return true;}
};

struct Explicit{
    explicit Explicit() {}
    explicit Explicit(int) {}
    explicit Explicit(int, int) {}
    explicit operator bool() const { return true;}
};

void funcNoExplicit(NoExplicit x) {}
void funcNoExplicitMultipleVals(NoExplicitMultipleVals x) {}
void funcNoExplicitMultipleVals2(NoExplicitMultipleVals2 x) {}
void funcExplicit(Explicit x) {}

void explicit_lab(){
    NoExplicit a1(1);
    NoExplicit a2(1, 1);
    NoExplicit a3 = 1;
    NoExplicit a4 = {1, 1};
    if(a4) {}
    bool b1 = a4;

    funcNoExplicit(1); // converts to NoExplicit using the NoExplicit(int) constructor
    // funcNoExplicit(); // fails - need an input param
    // will do an implicit conversion if there is constrcutor with one uninitialized value
    funcNoExplicitMultipleVals(1); // implicit call to NoExplicitMultipleVals(bool, int y =5, double=7.0, bool =false)
    // 1st bool value was the input 1 

    // funcNoExplicitMultipleVals2(1); // fails - no implicit conversion since it needs two values to construct
    // funcNoExplicitMultipleVals2(false, 2); // fails since you cant do an implicit conversion from two values
    funcNoExplicitMultipleVals2({false, 2}); // works but the construction is less implicit in this case


    Explicit c1(1);
    Explicit c2(1, 1);
    // Explicit c3 = 1; // has to explicitly call Explicit(int) constructor
    // Explicit c4 = {1, 1}; // has to explicitly call Explicit(int, int) constructor
    if(c2) {} // calls bool func
    // bool b2 = c2; // doesnt call bool func
    bool b2 = static_cast<bool>(c2); // calls bool func

    //funcExplicit(1); // fails - implicit conversions not allowed
    // has to send an explicit object
}