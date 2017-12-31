#include <iostream>
using charPtr = char*;
using std::cout;
using std::endl;
void reverseString(char str[],int size);

int main()
{
    char str[] = "war";
    int length = sizeof(str)/sizeof(str[0]);
    reverseString(str,length);
    for(int i = 0; i<length; i++)
        cout<<str[i];
    cout<<endl;
}

void reverseString(char str[],int size)
{
    charPtr head = str;
    charPtr tail= str+size-1;
    while(head<tail){
        char temp = *head;
        *head = *tail;
        *tail = temp;
        head++,tail--;
    }
}
