#include <iostream>

using namespace std;

int findSumMultiplies(int n);
int main()
{
    cout<<findSumMultiplies(1000)<<endl;
}

int findSumMultiplies(int n ){
    int sum = 0;
    for(int i =3; i<n;i++){
        if(i%3==0)
            sum+=i;
        else if(i%5==0)
            sum+=i;
    }
    return sum;
}
