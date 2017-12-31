//Given an array with nth length and a number k
//multiply all elements of n and return the remainder
//of the product and k
#include <iostream>

using namespace std;
int remainder(int arr[], int k, int length);
int main()
{
    int arr[] = {4,6,7};
    int k = 2;
    int length = sizeof(arr)/sizeof(arr[0]);
    cout<<remainder(arr,k,length)<<endl;
}

int remainder(int arr[],int k,int length){
    if(length==0)
        return 0;
    int sum = 1;
    for(int i = 0;i<length;i++)
        sum*=arr[i];
    return sum%k;
}
