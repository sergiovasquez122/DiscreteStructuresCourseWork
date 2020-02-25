#include "fraction.h"

fraction::fraction(int n, int d):num(n),denom(d)
{
        reduce();
}

fraction::fraction(double x){
    stringstream ss;
    ss<<x;
    string ans;
    ss>>ans;
    stringToFraction(ans);
}

fraction::fraction(string x)
{
    stringToFraction(x);
}

void fraction::stringToFraction(string x)
{
    int whole,decimalPart;
    int pos = x.find('.');
    int length = x.size()-1-pos;
    whole = atoi(x.substr(0,pos).c_str());
    decimalPart = atoi(x.substr(pos+1).c_str());
    denom = pow10(length);
    num = whole*denom+decimalPart;
}

fraction::~fraction(){

}

fraction::fraction(const fraction &other):num(other.num),denom(other.denom)
{}

fraction& fraction::operator= (const fraction& other)
{
    if(this != &other){
        num = other.num;
        denom = other.denom;
    }
    return *this;
}

fraction& fraction::operator +=(const fraction& other){
    *this = *this +other;
    return *this;
}


fraction& fraction::operator *=(const fraction& other)
{
    *this = *this*other;
    return *this;
}

fraction& fraction::operator -=(const fraction& other){
    *this = *this-other;
    return *this;
}

void fraction::set(int n, int d=1)
{
    num = n;
    denom = d;
    reduce();
}

int fraction::getNum()const
{
    return num;
}

int fraction::getDenom()const
{
    return denom;
}

void fraction::display()const
{
    cout<<num;
    if(denom!=1)
        cout<<"/"<<denom<<" ";
}

void fraction::input()
{
    char junk;
    cin>>num>>junk>>denom;
}

void fraction::reduce(){
    int div  = gcd(num,denom);
    num/=div;
    denom/=div;
    if(denom<0){
        num*=-1;
        denom*=-1;
    }
}

int fraction::gcd(int p, int q){
    return q==0?p:gcd(q,p%q);
}
