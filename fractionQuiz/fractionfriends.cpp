#include "fraction.h"

ostream& operator<<(ostream& out,const fraction& frac){
    out<<frac.num;
    if(frac.denom!=1)
        out<<"/"<<frac.denom;
    return out;
}

istream& operator>>(istream& in,fraction& frac){
    stringstream convert;
    char junk;
    frac.denom =1;
    in>>frac.num;
    if(in.peek()=='/'){
        in>>junk>>frac.denom;
        frac.reduce();
    }
    else
        if(in.peek()=='.'){
            int decimal;
            string ans(to_string(frac.num));//Get the whole number digits
            in>>junk;//Remove the .
            in>>decimal;
            string line = to_string(frac.num) + "."+to_string(decimal);
            frac = fraction(line);
        }
    return in;
}

fraction operator +(const fraction& x,const fraction& y)
{
    int num = x.num*y.denom+y.num*x.denom;
    int denom = x.denom*y.denom;
    return fraction(num,denom);
}

fraction operator -(const fraction& x,const fraction& y)
{
    int num = x.num*y.denom-y.num*x.denom;
    int denom = x.denom*y.denom;
    return fraction(num,denom);
}

fraction operator *(const fraction& x,const fraction& y)
{
    int num = x.num*y.denom*y.num*x.denom;
    int denom = x.denom*y.denom;
    return fraction(num,denom);
}

fraction operator /(const fraction& x,const fraction& y)
{
    int num = x.num*y.denom;
    int denom = x.denom*y.num;
    return fraction(num,denom);
}

bool operator ==(const fraction &x,const fraction& y){
    return x.num*y.denom==y.num*x.denom;
}

bool operator !=(const fraction& x,const fraction& y){
    return !(x==y);
}

bool operator<(const fraction& x,const fraction& y){
    return x.num*y.denom<y.num*x.denom;
}

bool operator>(const fraction& x,const fraction& y){
    return x.num*y.denom>y.num*x.denom;
}

bool operator <=(const fraction& x,const fraction& y)
{
    return !(x>y);
}


bool operator >=(const fraction& x,const fraction& y)
{
    return !(x<y);
}


