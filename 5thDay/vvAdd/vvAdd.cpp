#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <chrono>

#define VETSIZE 10000000

int main(){
#ifdef wiithMACRO
    std::srand(time(NULL));
    //unsigned int n = 10000000;
    std::vector<int>vetA(VETSIZE, rand());
    std::vector<int>vetB(VETSIZE, rand());
    std::vector<int>vetC(VETSIZE, 0);

    auto t1 = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for // ~515ms for 100000000 elements w/o OpenMP, ~158 with it
                             // ~51ms for 10000000 elements w/o OpenMP, ~15 with it 
    for(unsigned int i = 0; i < VETSIZE; ++i){
        vetC[i] = vetA[i] + vetB[i];
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration_sum_loop = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    int sum = 0;
    t1 = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for reduction(+:sum)
    for(unsigned int i = 0; i < VETSIZE; ++i){
        sum += vetC[i];
    }
    t2 = std::chrono::high_resolution_clock::now();
    auto duration_reduction_loop = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << duration_sum_loop << " miliseconds." << std::endl;
    std::cout << duration_reduction_loop << " miliseconds." << std::endl;
#else
    std::srand(time(NULL));
    //unsigned int n = 10000000;
    std::vector<int>vetA(VETSIZE, rand());
    std::vector<int>vetB(VETSIZE, rand());
    std::vector<int>vetC(VETSIZE, 0);

    auto t1 = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for // ~515ms for 100000000 elements w/o OpenMP, ~158 with it
                             // ~51ms for 10000000 elements w/o OpenMP, ~15 with it 
    for(unsigned int i = 0; i < vetC.size(); ++i){
        vetC[i] = vetA[i] + vetB[i];
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration_sum_loop = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    int sum = 0;
    t1 = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for reduction(+:sum)
    for(unsigned int i = 0; i < vetC.size(); ++i){
        sum += vetC[i];
    }
    t2 = std::chrono::high_resolution_clock::now();
    auto duration_reduction_loop = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << duration_sum_loop << " miliseconds." << std::endl;
    std::cout << duration_reduction_loop << " miliseconds." << std::endl;
#endif
}