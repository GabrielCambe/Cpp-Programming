#include <iostream>
#include <iomanip> // std::setprecision
#include <vector>

#include "matrix.h"

int main(){
    int n,m;
    n = 5; m = 5;
    Matrix mat = Matrix(n,m);
    mat.print(5, 10);
    mat(4,4) = 3.14159265;
    
    std::cout << mat(4,4) << std::endl;

    mat.print(5, 10);

    std::cout << mat << std::endl;
    
}
