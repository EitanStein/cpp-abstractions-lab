#include "cpp_abstractions_lab/optional.hpp"
#include <iostream>

int main(){
    Optional x;
    try{
        int z = x.value();
    }
    catch(const bad_optional_access& e){
        std::cout << e.what() << "\n";
    }
    
    std::cout << "x has value? " << x.has_value() << "\n";
    std::cout << "x's value is 4? " << (x == 4) << "\n";
    std::cout << "x's value is nullopt? " << (x == nullopt) << "\n";
    std::cout << "x's value is? or 42? " << x.value_or(42) << "\n\n";

    x = 4;
    std::cout << "x has value? " << x.has_value() << "\n";
    std::cout << "x's value is 4? " << (x == 4) << "\n";
    std::cout << "x's value is nullopt? " << (x == nullopt) << "\n";
    std::cout << "x's value is? or 42? " << x.value_or(42) << "\n";
    std::cout << "x's value is? " << x.value() << "\n\n";

    x = nullopt;
    std::cout << "x has value? " << x.has_value() << "\n";
    std::cout << "x's value is 4? " << (x == 4) << "\n";
    std::cout << "x's value is nullopt? " << (x == nullopt) << "\n\n";

    x = 42;
    std::cout << "x has value? " << x.has_value() << "\n";
    x.reset();
    std::cout << "x has value? " << x.has_value() << "\n";
    return 0;
}