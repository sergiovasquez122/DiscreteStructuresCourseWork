//Write a program to find the smallest positive number that is 
//evenly divisble by all numbers from 1 to 20 
#include <iostream>

using namespace std;

int smallestMultiple();

int main()
{
    cout<<smallestMultiple()<<endl;
}

int smallestMultiple(){
    for(size_t i = 20;;i++){
        for(size_t j = 1; j<=20&&i%j==0;j++){
            if(j==20)
                return i;
        }
    }
    return 0;
}
