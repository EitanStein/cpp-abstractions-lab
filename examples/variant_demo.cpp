#include "../include/cpp_abstractions_lab/variant.hpp"
#include <iostream>


int main(){

    Variant<int, double> v(4.4);
    double x = v.get<double>();

    return 0;
}