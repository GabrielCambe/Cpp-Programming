#include <iostream> // cout, cin, endl
#include <vector> // vetor
#include <algorithm> // generate
#include <ctime> // time
#include <cstdlib> // rand, srand

using intMatrix = std::vector<std::vector<int>> ;

// 3. Write a function "add" that adds two integers, which are passed as arguments to that function.
//auto lambdaAdd = []( int a, int b ){ return a+b; };

int add(int a, int b){
    return a+b;
};

// 4. Write a void function "matReduce", which takes a matrix, an integer "red" (by reference), and a function pointer "pf" as parameters.
// a. The function pointer takes two integers and returns an integer.
void matReduce( intMatrix &mat, int *red, int(*pf)(int, int) ){
    // b. Iterate through the whole matrix and perform for each entry matVal red = pf(red, matVal)
    for(unsigned int i = 0; i < mat.size(); ++i){
        for(unsigned int j = 0; j < mat[i].size(); ++j){
            *red = pf(*red, mat[i][j]);
            std::cout << mat[i][j] << " "; 
        }
        std::cout << std::endl;
        //std::for_each(mat[ i ].begin(), mat[ i ].end(), add );
    }

    // for(unsigned int i = 0; i < mat.size(); ++i){
    //     for(unsigned int j = 0; j < mat[i].size(); ++j){
    //          std::cout << mat[i][j] << " "; 
    //     }
    //     std::cout << std::endl;
    // }
}

int main(){
    std::srand(std::time(NULL));

    int entryMax = 20;
    auto limitedRand = [entryMax](){ return (std::rand() % entryMax); };

    // 2. Generate a matrix (consisting of a vector of vectors of integers) of random size and random entries.
    unsigned int matSize = limitedRand();
    intMatrix matrix( matSize, std::vector<int> (matSize) );
    for(unsigned int it = 0; it < matSize; ++it){
        std::generate(matrix[ it ].begin(), matrix[ it ].end(), limitedRand );
    }

    // 5. Use "matReduce" and "add" to get the sum of all matrix entries.
    int reduce = 0;
    matReduce( matrix, &reduce, add );
    std::cout << "Reduce: "<< reduce << std::endl;

    // 6. What other reduction operations (instead of getting the sum) could be done here? Create some on your own.
    auto lambdaMult = [](int a, int b ){ return a*b; };
    auto lambdaDiv = [](int a, int b ){ return a/b; };

    // 7. Use lambda functions as input for "matReduce".
    reduce = 0;
    matReduce( matrix, &reduce, lambdaMult );
    std::cout << "Reduce: "<< reduce << std::endl;

    reduce = 0;
    matReduce( matrix, &reduce, lambdaDiv );
    std::cout << "Reduce: "<< reduce << std::endl;


}

