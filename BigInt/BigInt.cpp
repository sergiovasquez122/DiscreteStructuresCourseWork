#include "BigInt.h"

BigInt::BigInt() {
    storage.push_back(0);
}

BigInt::BigInt(int digit) {
    string value = to_string(digit);
    *this = BigInt(value);
}

BigInt::BigInt(const string& digits) {
    for(string::const_reverse_iterator rit = digits.crbegin(); rit != digits.crend(); ++rit){
        storage.push_back(*rit - '0');
    }
}

size_t BigInt::size() const {
    return storage.size();
}

void BigInt::print() {
    for(vector<char>::reverse_iterator rit = storage.rbegin(); rit != storage.rend();++rit){
        cout << (int) *rit;
    }
}

BigInt operator+(const BigInt &lhs, const BigInt &rhs) {
    string result;
    vector<char>::const_iterator lhs_it = lhs.storage.cbegin();
    vector<char>::const_iterator rhs_it = rhs.storage.cbegin();

    int carry = 0;
    while(lhs_it != lhs.storage.cend() && rhs_it != rhs.storage.cend()){
        int sum = *lhs_it + * rhs_it + carry;
        carry = sum / 10;
        result.push_back((sum % 10) + '0');
        ++lhs_it;
        ++rhs_it;
    }

    while(lhs_it != lhs.storage.cend()) {
        int sum = *lhs_it + carry;
        carry = sum / 10;
        result.push_back((sum % 10) + '0');
        ++lhs_it;
    }

    while(rhs_it != rhs.storage.cend()) {
        int sum = *rhs_it + carry;
        carry = sum / 10;
        result.push_back((sum % 10) + '0');
        ++rhs_it;
    }
    if(carry){
        result.push_back(carry + '0');
    }
    return BigInt({result.rbegin(), result.rend()});
}

BigInt operator+(const BigInt &lhs, int rhs) {
    return lhs + BigInt(rhs);
}

BigInt operator+(int lhs, const BigInt &rhs) {
    return rhs + lhs;
}

ostream &operator<<(ostream &os, const BigInt &bigInt) {
    vector<char>::const_reverse_iterator it = bigInt.storage.crbegin();
    vector<char>::const_reverse_iterator end = bigInt.storage.crend();
    if(bigInt.size() < 13){
        while(it != end){
            os << (int) *it ++;
        }
    } else {
        os << (int) *it++ << ".";
        end = it + 10;
        while(it != end){
            os << (int) *it++;
        }
        os << "e" + to_string(bigInt.size());
    }
    return os;
}


bool operator==(const BigInt &lhs, const BigInt &rhs) {
    if(lhs.size() != rhs.size()){
        return false;
    }
    for(int i = 0; i < lhs.size();++i){
        if(lhs.storage[i] != rhs.storage[i]){
            return false;
        }
    }
    return true;
}

bool operator==(const BigInt &lhs, int rhs) {
    return lhs == BigInt(rhs);
}

bool operator==(int lhs, const BigInt &rhs) {
    return rhs == lhs;
}

bool operator!=(const BigInt &lhs, const BigInt &rhs) {
    return !(lhs == rhs);
}

bool operator!=(const BigInt &lhs, int rhs) {
    return lhs != BigInt(rhs);
}

bool operator!=(int lhs, const BigInt &rhs) {
    return rhs != lhs;
}

bool operator<(const BigInt &lhs, const BigInt &rhs) {
    if(lhs.size() < rhs.size()) return true;
    if(lhs.size() > rhs.size()) return false;
    int length = lhs.size();
    for(int i = length - 1;i >= 0;--i){
        if(lhs.storage[i] != rhs.storage[i]){
            return lhs.storage[i] < rhs.storage[i];
        }
    }
    return false;
}

bool operator<(const BigInt &lhs, int rhs) {
    return lhs < BigInt(rhs);
}

bool operator<(int lhs, const BigInt &rhs) {
    return BigInt(lhs) < rhs;
}

bool operator>(const BigInt &lhs, const BigInt &rhs) {
    return rhs < lhs;
}

bool operator>(const BigInt &lhs, int rhs) {
    return lhs > BigInt(rhs);
}

bool operator>(int lhs, const BigInt & rhs) {
    return BigInt(lhs) > rhs;
}

bool operator<=(const BigInt &lhs, const BigInt &rhs) {
    return !(lhs > rhs);
}

bool operator<=(const BigInt &lhs, int rhs) {
    return lhs <= BigInt(rhs);
}

bool operator<=(int lhs, const BigInt &rhs) {
    return BigInt(lhs) <= rhs;
}

bool operator>=(const BigInt &lhs, const BigInt &rhs) {
    return !(lhs < rhs);
}

bool operator>=(const BigInt &lhs, int rhs) {
    return lhs >= BigInt(rhs);
}

bool operator>=(int lhs, const BigInt &rhs) {
    return lhs >= BigInt(rhs);
}

BigInt &BigInt::operator++() {
    *this = *this + 1;
    return *this;
}

BigInt BigInt::operator++(int) {
    BigInt ret(*this);
    ++*this;
    return ret;
}

BigInt operator-(const BigInt &lhs, const BigInt &rhs) {
    string result;
    vector<char>::const_iterator lhs_it = lhs.storage.cbegin();
    vector<char>::const_iterator rhs_it = rhs.storage.cbegin();
    int carry = 0;
    for(;lhs_it != lhs.storage.cend() && rhs_it != rhs.storage.cend();++lhs_it, ++rhs_it) {
        int diff = *lhs_it - *rhs_it - carry;
        if (diff < 0) {
            carry = 1;
            diff += 10;
        } else carry = 0;
        result.push_back(diff + '0');
    }
    for(; lhs_it != lhs.storage.cend(); ++lhs_it){
        int diff = *lhs_it - carry;
        if(diff < 0){
            carry = 1;
            diff += 10;
        } else carry = 0;
        result.push_back(diff + '0');
    }
    while(result.back() == '0' && result.size() > 1) result.pop_back();
    return BigInt({result.rbegin(), result.rend()});
}

BigInt operator-(const BigInt &lhs, int rhs) {
    return lhs - BigInt(rhs);
}

BigInt operator-(int lhs, const BigInt &rhs) {
    return BigInt(lhs) - rhs;
}

