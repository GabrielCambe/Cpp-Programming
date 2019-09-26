#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h> // for assert(condition)

// struct Matrix {
//     std::vector<double> vals;
//     unsigned int n;
//     unsigned int m;
//     Matrix(unsigned int n, unsigned int m){
//         this->n = n;
//         this->m = m;
//         for(unsigned int i = 0; i < this->n; ++i ){
//             for(unsigned int j = 0; j < this->m; ++j){
//                 this->vals.push_back(0.0);
//             }   
//         }
//     }
//     public:
//         void print( int prec, int spaces ){
//             std::cout << std::fixed; // represents floating point numbers in fixed point notation in a io operation
//             std::cout << std::setw(spaces);
//             for(unsigned int i = 0; i < this->n; ++i ){
//                 for(unsigned int j = 0; j < this->m; ++j){
//                     std::cout << std::setprecision(prec) << this->vals[(i*m)+j] << " ";
//                 }
//                 std::cout << std::endl;
//             }
//         }
// };

class Matrix {
    private:
        std::vector<double> vals;
        unsigned int n;
        unsigned int m;
    public:
        double getVal(int i, int j){
            return this->vals[(i*m)+j];
        }

        void setVal(int i, int j, double val){
            this->vals[(i*m)+j] = val;
        }

        void print( int prec, int spaces ){
            std::cout << std::fixed; // represents floating point numbers in fixed point notation in a io operation
            for(unsigned int i = 0; i < this->n; ++i ){
                for(unsigned int j = 0; j < this->m; ++j){
                    std::cout << std::setprecision(prec) << this->vals[(i*m)+j] << std::setw(spaces);
                }
                std::cout << std::endl;
            }
        }

    // std::vector< n, std::vector<double>>, try to re-implement with this vector
    Matrix(unsigned int n, unsigned int m){
        this->n = n;
        this->m = m;
        for(unsigned int i = 0; i < this->n; ++i ){
            for(unsigned int j = 0; j < this->m; ++j){
                this->vals.push_back(0.0);
            }   
        }
    }
};


#endif