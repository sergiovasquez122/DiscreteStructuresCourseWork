#ifndef FRACTION_H
#define FRACTION_H
#include <sstream>
#include <iostream>
#include <cmath>
using namespace std;
class fraction
{
public:
    fraction(int n = 0,int d =1);
    fraction(double x);
    fraction(string x);
    ~fraction();
    fraction(const fraction& other);
    fraction& operator=(const fraction&);
    fraction& operator+=(const fraction& other);
    fraction& operator-=(const fraction& other);
    fraction& operator*=(const fraction&);
    fraction& operator/=(const fraction&);
    void set(int n,int d);
    int getNum()const;
    int getDenom()const;
    void display()const;
    void input();
    friend ostream& operator<<(ostream& out,const fraction&);
    friend istream& operator>>(istream&,fraction&);
    friend
    fraction operator+(const fraction& x,const fraction&);
    friend
    fraction operator-(const fraction&,const fraction &);
    friend
    fraction operator/(const fraction&,const fraction&);
    friend
    fraction operator*(const fraction&,const fraction&);
    friend
    bool operator==(const fraction&,const fraction&);
    friend
    bool operator!=(const fraction&,const fraction&);
    friend
    bool operator <(const fraction&,const fraction&);
    friend
    bool operator>(const fraction&,const fraction&);
    friend
    bool operator<=(const fraction&,const fraction&);
    friend
    bool operator>=(const fraction&,const fraction&);
private:
    int num,denom;
    void reduce();
    int gcd(int p,int q);
    void stringToFraction(string x);
};

#endif // FRACTION_H
