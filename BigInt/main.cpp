#include <iostream>
#include <map>
#include "BigInt.h"

using namespace std;
int goldRabbits(int);
BigInt goldRabbits(BigInt);

void pause() { cout << "Press Enter to continue..."; getchar();}

int main() {
    BigInt B1("123456789123456789123456789123456789");
    BigInt B2(B1);
    BigInt MAX(INT32_MAX);
    cout << "B1:"<< B1 << "\nB2:" << B2 <<"\nMAX:"<<MAX<<endl;
    pause();
    cout <<"\nB1:";
    B1.print();
    cout << endl;
    pause();

    for(BigInt i = 0; i <= 3000;i++){
        cout << "\ngoldRabbits(" << i <<") = " << goldRabbits(i);
    }
    pause();

    cout << "\nThis is the value of goldRabbits(3000)\n\n";
    BigInt gR3000 = goldRabbits(BigInt(3000));
    gR3000.print();
    pause();
}

BigInt goldRabbits(BigInt n){
    static map<BigInt, BigInt> table;
    if(n == 0 || n == 1)
        return BigInt(1);
    if(table.find(n) == table.end()){
        table[n] = goldRabbits(n-1) + goldRabbits(n-2);
    }
    return table[n];
}

int goldRabbits(int n){
    if(n == 0 || n == 1)
        return 1;
    else
        return goldRabbits(n - 1) + goldRabbits(n - 2);
}
