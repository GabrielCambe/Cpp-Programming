#include <iostream>

template <typename Type>
Type add( Type a, Type b ) {
    return a+b;
}

int main(){
    std::cout << add(4.5, 4.5) << std::endl;
    std::cout << add(12, 3) << std::endl;
    
    std::cout << add<int>(4.5, 4.5) << std::endl;
    
}  
