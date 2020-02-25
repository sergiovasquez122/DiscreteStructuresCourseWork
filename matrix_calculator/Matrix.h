//
// Created by sergio on 10/15/18.
//

#ifndef MATRIX_CALCULATOR_MATRIX_H
#define MATRIX_CALCULATOR_MATRIX_H

#include "Fraction.h"
#include <vector>

using std::vector;
using std::cin;

template<typename T>
class Matrix {
public:

    Matrix(int r,int c);

    Matrix<T> inversion();

    Matrix<T> transpose();

    vector<T> &operator[](int i);

    template<typename U>
    friend Matrix<U> operator +(Matrix<U>& x,Matrix<U>& y);

    template<typename U>
    friend Matrix<U> operator -(Matrix<U>& x,Matrix<U>& y);

    template<typename U>
    friend Matrix<U> operator *(Matrix<U>& x,Matrix<U>& y);

    template<typename U>
    friend ostream& operator<<(ostream& out,Matrix<U>& x);

    template<typename U>
    friend istream& operator>>(istream& in,Matrix<U>& x);

private:
    vector<vector<T>> matrix;
    int rows,cols;
};

template<typename T>
Matrix<T>::Matrix(int r, int c) :matrix(r)
{
    rows = r;
    cols = c;

    for(int i = 0;i<rows;++i)
        matrix[i].resize(c);
}

template<typename T>
Matrix<T> Matrix<T>::inversion() {
    return Matrix(0, 0);
}

template<typename T>
vector<T> & Matrix<T>::operator[](int i) {
    return matrix[i];
}

template<typename T>
Matrix<T> operator+(Matrix<T> &x,Matrix<T> &y) {
    if(x.rows==y.rows&&x.cols==y.cols){
        Matrix<T> m(x.rows,x.cols);
        for(int i = 0;i<x.rows;++i){
            for(int j = 0;j<x.cols;++j){
                m[i][j] = x[i][j]+y[i][j];
            }
        }
        return m;
    }
    throw std::runtime_error("Incompatible  matrix sizes for addition");
}

template<typename T>
Matrix<T> operator-(Matrix<T> &x, Matrix<T> &y) {
    if(x.rows==y.rows&&x.cols==y.cols){
        Matrix<T> m(x.rows,x.cols);
        for(int i = 0;i<x.rows;++i){
            for(int j = 0;j<x.cols;++j){
                m[i][j] = x[i][j]-y[i][j];
            }
        }
        return m;
    }
    throw std::runtime_error("Incompatible matrix sizes for subtraction");
}

template<typename T>
Matrix<T> Matrix<T>::transpose(){
    Matrix<T> m(cols,rows);
    for(int i = 0;i<rows;++i) {
        for(int j = 0;j<cols;++j){
            m[j][i] = matrix[i][j];
        }
    }
    return m;
}

template<typename T>
ostream& operator<<(ostream& out,Matrix<T>& x){
    if(&out == &std::cout) {
        for (int i = 0; i < x.rows; ++i) {
            for (int j = 0; j < x.cols; ++j) {
                out << x[i][j] << " ";
            }
            out << "\n";
        }
    }
    else {
        out<<x.rows<<" "<<x.cols<<" ";
        for (int i = 0; i < x.rows; ++i) {
            for (int j = 0; j < x.cols; ++j) {
                out << x[i][j]<<std::endl;
            }
        }
    }
    return out;
}

template<typename U>
istream& operator>>(istream &in, Matrix<U> &x) {
    if(&in==&cin){
        std::cout<<"Enter the rows and columns amount seperated by spaces: ";
        int row,col;
        in>>row>>col;
        x = Matrix<U>(row,col);
        x.rows = row,x.cols = col;
        in.ignore();
        for(int i = 0;i<x.rows;++i){
            for(int j = 0;j<x.cols;++j){
                std::cout<<"Position "<<i<<" "<<j<<" : ";
                in>>x[i][j];
            }
        }
    }
    else {
        //reading in from file.
        int row,col;
        in>>row>>col;
        x = Matrix<U>(row,col);
        for(int i = 0;i<x.rows;++i){
            for(int j = 0;j<x.cols;++j){
                in>>x[i][j];
            }
        }
    }
    return in;
}

template<typename T>
Matrix<T> operator*(Matrix<T> &x, Matrix<T> &y) {
    if(x.cols!=y.rows)throw std::runtime_error("Incompatible matrix sizes");
    Matrix<T> ret(x.rows,y.cols);
    for(int i = 0;i<x.rows;++i){
        for(int j = 0;j<y.cols;++j){
            T sum = 0;
            for(int k = 0;k<x.cols;++k)
                sum = sum+x[i][k]*y[k][j];
            ret[i][j] = sum;
        }
    }
    return ret;
}

#endif //MATRIX_CALCULATOR_MATRIX_H
