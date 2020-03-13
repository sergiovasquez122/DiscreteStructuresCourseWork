#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H

#include <iostream>
#include <vector>

using namespace std;

class BigInt {
public:
    BigInt();
    BigInt(int);
    BigInt(const string&);
    BigInt& operator++();
    BigInt operator++(int);
    size_t size() const ;
    void print();

    friend
    BigInt operator+(const BigInt&, const BigInt&);
    friend
    BigInt operator+(const BigInt&, int);
    friend
    BigInt operator+(int, const BigInt&);
    friend
    ostream& operator<<(ostream&, const BigInt&);

    friend
    BigInt operator-(const BigInt&, const BigInt&);

    friend
    BigInt operator-(const BigInt&, int );

    friend
    BigInt operator-(int, const BigInt&);

    friend
    bool operator==(const BigInt&, const BigInt&);

    friend
    bool operator==(const BigInt&, int);

    friend
    bool operator==(int, const BigInt&);

    friend
    bool operator!=(const BigInt&, const BigInt&);

    friend
    bool operator!=(const BigInt&, int);

    friend
    bool operator!=(int, const BigInt&);

    friend
    bool operator<(const BigInt&, const BigInt&);

    friend
    bool operator<(const BigInt&, int);

    friend
    bool operator<(int, const BigInt&);

    friend
    bool operator>(const BigInt&, const BigInt&);

    friend
    bool operator>(const BigInt&, int);

    friend
    bool operator>(int, const BigInt&);

    friend
    bool operator<=(const BigInt&, const BigInt&);

    friend
    bool operator<=(const BigInt&, int);

    friend
    bool operator<=(int, const BigInt&);

    friend
    bool operator>=(const BigInt&, const BigInt&);

    friend
    bool operator>=(const BigInt&, int);

    friend
    bool operator>=(int, const BigInt&);
private:
    vector<char> storage;
};


#endif //BIGINT_BIGINT_H
