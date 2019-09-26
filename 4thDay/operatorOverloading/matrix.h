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
                    std::cout << std::setprecision(prec) << std::setw(spaces) << this->vals[(i*m)+j];
                }
                std::cout << "\n" << std::endl;
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

    // double& operator()(int i, int j){
    //     return this->vals[(i*this->n)+j];
    // }
    double operator()(int i, int j) const { // Implements get function for const classes
        return this->vals[(i*this->n)+j];
    }

    // void operator()(int i, int j, double val){
    //     this->vals[(i*this->n)+j] = val;
    // }
    double& operator()(int i, int j){ // Implements get & set funcion for variable classes
        return (this->vals[(i*this->n)+j]);
    }

    int printPrec;
    int printSpce;

    // inline std::ostream operator<<(std::ostream& out, const Matrix& mat) const {
    //     //out << std::fixed; // represents floating point numbers in fixed point notation in a io operation
    //     for(unsigned int i = 0; i < mat.n; ++i ){
    //         for(unsigned int j = 0; j < mat.m; ++j){
    //             out << std::fixed << std::setprecision(mat.printPrec) << std::setw(mat.printSpce) << mat.vals[(i*m)+j];
    //         }
    //         out << "\n" << std::endl;
    //     }
    //     return out;
    // }



};

#endif