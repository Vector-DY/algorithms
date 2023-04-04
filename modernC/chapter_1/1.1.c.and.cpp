#include "foo.h"
#include <iostream>
#include <functional>

int main()
{
    // lambda
    [out = std::ref(std::cout << "Result from C code :" << add(1,2))](){
        out.get() << ".\n";
    }();
    return 0;
}