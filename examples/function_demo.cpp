#include "cpp_abstractions_lab/function.hpp"
#include <iostream>

int myIntFunc(int x){
    return x*2;
}

void myVoidFunc(){
    std::cout << "my Void func\n";
}

int main(){
    {
        Function<int(int)> func(&myIntFunc);
        std::cout << func(2) << "\n";
    }
    {
        Function<void()> func(&myVoidFunc);
        func();
    }
    {
        Function<int(int,int)> func{[](int x,int y) -> int{ return x+y;}};
        std::cout << func(2,5) << "\n";
    }
    {
        Function<int(int,int)> func{[](int x,int y) -> int{ return x+y;}};
        func = {[](int x,int y) -> int{ return x*y;}};
        std::cout << func(2,5) << "\n";
    }
    {
        Function<int(int,int)> func1;
        Function<int(int,int)> func2{[](int x,int y) -> int{ return x+y;}};
        func1 = func2;
        std::cout << func1(2,5) << "\n";
        if(func2)
            std::cout << func2(2,7) << "\n";
    }
    {
        Function<int(int,int)> func1;
        Function<int(int,int)> func2{[](int x,int y) -> int{ return x+y;}};
        func1 = std::move(func2);
        std::cout << func1(2,5) << "\n";
        if(func2)
            std::cout << func2(2,7) << "\n";
    }
    return 0;
}