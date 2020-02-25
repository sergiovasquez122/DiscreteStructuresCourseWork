//
// Created by sergio on 10/15/18.
//

#ifndef MATRIX_CALCULATOR_FRACTION_H
#define MATRIX_CALCULATOR_FRACTION_H

#include <regex>
#include <iostream>
#include <cassert>
#include <sstream>
using std::ostream;
using std::istream;
using std::string;
using std::regex;

class Fraction {
public:
    Fraction(int n = 0,int d = 1);

    Fraction(string number);

    Fraction(double num);

    int getNumerator() const;

    int getDenominator()const;

    double getValue() const;

    friend Fraction operator*(const Fraction& x,const Fraction& y);

    friend Fraction operator+(const Fraction& x,const Fraction& y);

    friend Fraction operator-(const Fraction& x,const Fraction&y);

    friend Fraction operator/(const Fraction& x,const Fraction&y);

    friend ostream& operator<<(ostream& out,const Fraction& frac);

    friend istream& operator>>(istream& in,Fraction& frac);

    bool operator <(const Fraction& rhs);

    bool operator >(const Fraction& rhs);

    bool operator <=(const Fraction& rhs);

    bool operator >=(const Fraction& rhs);

    bool operator ==(const Fraction& rhs);

    bool operator !=(const Fraction& rhs);

private:
    void valid();
    int gcd(int p,int q);
    int n,d;
};


#endif //MATRIX_CALCULATOR_FRACTION_H
