#include "../include/cpp_abstractions_lab/variant.hpp"
#include <iostream>
#include <string>


struct MyStruct{
    int x;
    int y;
    double z;
    bool flag;
};

int main(){

    Variant<int, double, std::string, MyStruct> v(4.4);

    double x = v.get<double>();
    try{
        v.get<std::string>();
    }
    catch(bad_variant_access& e){
        std::cout << e.what() << "\n";
    }

    v = std::string("hello");

    std::cout << v.get<std::string>() << "\n";

    MyStruct my_struct{1,2,4.0,true};
    v = my_struct;

    std::cout << v.get<MyStruct>().z << "\n";


    {
        Variant<int, double, std::string, MyStruct> v2{MyStruct{1,2,5.5,true}};
        v = v2;
    }
    std::cout << v.get<MyStruct>().z << "\n";
    
    {
        Variant<int, double, std::string, MyStruct> v2{std::string("string here")};
        v = std::move(v2);
    }
    std::cout << v.get<std::string>() << "\n";


    {
        Variant<int, double, std::string> v2{std::string("string here")};
        // v = v2; // ERROR not the same variant types so can't copy
    }


    return 0;
}