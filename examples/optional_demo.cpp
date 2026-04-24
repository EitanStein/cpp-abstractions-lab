#include "cpp_abstractions_lab/optional.hpp"
#include <iostream>

int main(){
    Optional<std::string> x;
    try{
        std::string z = x.value();
    }
    catch(const bad_optional_access& e){
        std::cout << e.what() << "\n";
    }
    
    std::cout << "x has value? " << x.has_value() << "\n";
    std::cout << "x's value is 4? " << (x == "4") << "\n";
    std::cout << "x's value is nullopt? " << (x == nullopt) << "\n";
    std::cout << "x's value is? or default to 42? " << x.value_or("42") << "\n\n";

    x = std::string("44");
    std::cout << "x has value? " << x.has_value() << "\n";
    std::cout << "x's value is 4? " << (x == "4") << "\n";
    std::cout << "x's value is nullopt? " << (x == nullopt) << "\n";
    std::cout << "x's value is? or default to 42? " << x.value_or("42") << "\n";
    std::cout << "x's value is? " << x.value() << "\n\n";

    x = nullopt;
    std::cout << "x has value? " << x.has_value() << "\n";
    std::cout << "x's value is the string 'nullopt'? " << (x == "nullopt") << "\n";
    std::cout << "x's value is nullopt? " << (x == nullopt) << "\n\n";

    x = std::string("42");
    std::cout << "x has value? " << x.has_value() << "\n";
    x.reset();
    std::cout << "x has value? " << x.has_value() << "\n\n";
    
    Optional<std::string> y("something something");
    x = y;
    std::cout << "y has value? " << y.has_value() << "\n";
    std::cout << "x has value? " << x.has_value() << "\n";
    x.reset();
    std::cout << "y has value? " << y.has_value() << "\n";
    x = std::move(y);
    std::cout << "y has value? " << y.has_value() << "\n";
    Optional<std::string> z(std::move(x));
    std::cout << "x has value? " << x.has_value() << "\n";
    std::cout << "z has value? " << z.has_value() << "\n";
    std::cout << "z's value is " << z.value() << "\n\n";


    return 0;
}