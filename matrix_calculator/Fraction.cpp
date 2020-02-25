//
// Created by sergio on 10/15/18.
//

#include "Fraction.h"

Fraction::Fraction(int numerator, int denominator) {
    int g = gcd(numerator,denominator);

    numerator/=g;
    denominator/=g;

    if(denominator<0){
        n = -numerator;
        d = -denominator;
    }
    else{
        n = numerator;
        d = denominator;
    }
    valid();
}

Fraction::Fraction(string number) {
    int whole = stoi(number.substr(0,number.find('.')));

    int decimal = stoi(number.substr(number.find('.')+1));

    int length = log10(decimal)+1;

    int demoninator = pow(10,length);

    int top = whole*demoninator;

    top = abs(top) + decimal;

    if(whole<0){
        top*=-1;
    }

    n = top;
    d = demoninator;

    *this = Fraction(n,d);
}

Fraction::Fraction(double num)
{
    std::stringstream ss;
    ss<<num;
    *this = Fraction(ss.str());
}

void Fraction::valid(){
    assert(d>0);
    assert(abs(gcd(n,d))==1);
}

int Fraction::gcd(int p, int q) {
    return p%q==0?q:gcd(q,p%q);
}

int Fraction::getDenominator() const {
    return d;
}

int Fraction::getNumerator() const {
    return n;
}

Fraction operator*(const Fraction &x, const Fraction &y) {
    return Fraction{x.n*y.n,x.d*y.d};
}

Fraction operator+(const Fraction &x, const Fraction &y) {
    return Fraction{x.n*y.d+y.n*x.d,x.d*y.d};
}

Fraction operator-(const Fraction &x, const Fraction &y) {
    return Fraction{x.n*y.d-y.n*x.d,x.d*y.d};
}

Fraction operator/(const Fraction& x,const Fraction& y){
    return Fraction{x.n*y.d,x.d*y.n};
}

ostream &operator<<(ostream &out, const Fraction &frac) {
    int whole = frac.n/frac.d;
    int numerator = frac.n%frac.d;
    if(frac.n==0)out<<"0";
    else if(whole == 0){
        out<<numerator<<'/'<<frac.d;
    }
    else if(numerator==0){
        out<<whole;
    }
    else {
        out<<whole<<" "<<abs(numerator)<<"/"<<frac.d;
    }
    return out;
}

double Fraction::getValue() const {
    return (double) n/d;
}

istream &operator>>(istream &in,Fraction &frac) {
    std::string expression;
    std::getline(in,expression);
    //Whole number
    std::stringstream ss(expression);
    if(regex_match(expression,regex(" *-?[0-9]+"))) {
        ss>>frac.n;
        frac.d = 1;
    }
    //fraction
    else if(regex_match(expression,regex(" *-?[0-9]+/[1-9][0-9]*"))){
        ss>>frac.n;
        //throwing away the '/'
        ss.ignore();
        ss>>frac.d;
    }
    else if(regex_match(expression,regex(" *-?[0-9]+ [0-9]+/[1-9][0-9]*"))){
        int whole,numerator;
        char junk;
        ss>>whole>>numerator>>junk>>frac.d;
        //converting number to improper fraction
        int top = whole*frac.d;
        numerator += abs(top);
        if(whole<0) numerator*=-1;
        frac.n = numerator;
    }
    else if(regex_match(expression,regex(" *-?[0-9]+[.][0-9]*"))){
        frac = Fraction(expression);
    }
    else if(expression.empty())return in;
    else throw std::runtime_error("Invalid input");
    return in;
}

bool Fraction::operator==(const Fraction &rhs) {
    return (n==rhs.n) && (d==rhs.d);
}

bool Fraction::operator!=(const Fraction &rhs) {
    return !(*this==rhs);
}

bool Fraction::operator<(const Fraction &rhs) {
    int x = n*rhs.d;
    int y = d*rhs.n;
    return x<y;
}

bool Fraction::operator>(const Fraction &rhs) {
    int x = n*rhs.d;
    int y = d*rhs.n;
    return x>y;
}

bool Fraction::operator<=(const Fraction &rhs) {
    int x = n*rhs.d;
    int y = d*rhs.n;
    return x<=y;
}

bool Fraction::operator>=(const Fraction &rhs) {
    int x = n*rhs.d;
    int y = d*rhs.n;
    return x>=y;
}
