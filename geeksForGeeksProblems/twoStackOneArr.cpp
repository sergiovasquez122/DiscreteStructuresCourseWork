//implement two stack using one array
#include <iostream>
#define MAX_STACK 50
using namespace std;
void pushStack1(int stack[], int &topStack1, const int value);
void pushStack2(int stack[], int &topStack2, const int value);
void popStack1(int arr[], int &topStack1);
void popStack2(int arr[], int &topStack2);
void displayStack(int arr[], int topstack1, int topStack2);

int main()
{
    int min;
    int stack[MAX_STACK];
    int topStack1 = -1;
    int topStack2 = MAX_STACK/2-1;
    pushStack1(stack,topStack1,12);
    pushStack1(stack,topStack1,13);
    pushStack1(stack,topStack1,20);
    pushStack2(stack,topStack2,12);
    pushStack2(stack,topStack2,12);
    pushStack2(stack,topStack2,12);
    displayStack(stack,topStack1,topStack2);
}

void pushStack1(int stack[],int &topStack1,const int value){
    if(topStack1==MAX_STACK/2-1)
        cout<<"Stack is full delete items"<<endl;
    else
        stack[++topStack1]=value;
}

void pushStack2(int stack[],int &topStack2,const int value){
    if(topStack2==MAX_STACK-1)
        cout<<"Stack is full delete items"<<endl;
    else
        stack[++topStack2]=value;
}

void popStack1(int arr[],int &topStack1){
    if(topStack1==-1)
        cout<<"Impossible no items"<<endl;
    else
        topStack1--;
}

void popStack2(int arr[],int &topStack2){
    if(topStack2==MAX_STACK/2-1)
        cout<<"Impossible no items"<<endl;
    else
        topStack2--;
}

void displayStack(int arr[],int topstack1,int topStack2){
    cout<<"The content of the first stack"<<endl;
    while(topstack1!=-1){
        cout<<arr[topstack1--]<<" ";
    }
    cout<<endl;
    cout<<"The content of the second stack"<<endl;
    while(topStack2!=MAX_STACK/2-1){
        cout<<arr[topStack2--]<<" ";
    }
    cout<<endl;
}
