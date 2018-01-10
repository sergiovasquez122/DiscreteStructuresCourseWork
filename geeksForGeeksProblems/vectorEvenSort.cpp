//GeekforGeeks problem: Given an array containing even and odd numbers
//sort the elements such that all the even numbers are in front and
//without using any additional data structure
#include <iostream>
#include <vector>
using u_int = unsigned int;
using std::string;
using std::vector;
using std::cout;
using std::endl;
void display(string title, vector<int> &vec);
void evenInFrontSort(vector<int> &vec);
void intSwap(int &a, int &b);

int main()
{
    vector<int> test;
    for(int i =0;i<10;i++)
        test.push_back(i);
    display("Before even sort: ",test);
    evenInFrontSort(test);
    display("After even sort: ",test);
}

void evenInFrontSort(vector<int> &vec){
    int nextEven = 0;
    int nextOdd = vec.size()-1;
    while(nextEven<nextOdd){
        if(vec[nextEven]%2==0)
            nextEven++;
        else
            intSwap(vec[nextEven],vec[nextOdd--]);
    }
}

void display(string title,vector<int> &vec){
    cout<<title<<endl;
    for(u_int i = 0; i <vec.size();i++)
        cout<<vec[i]<<" ";
    cout<<endl;
}

void intSwap(int &a,int &b){
    int temp = a;
    a = b;
    b = temp;
}
