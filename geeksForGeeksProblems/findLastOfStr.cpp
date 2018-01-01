//Find last index of particular char value
#include <iostream>

using namespace std;

int findLastIndex(string str, char target);
int main()
{
    string test = "mississipi";
    cout<<findLastIndex(test,'p')<<endl;
}

int findLastIndex(string str,char target){
    int index = -1;
    for(int i = 0; i <str.length(); i++)
        if(str[i]==target)
            index = i;
    return index;
}
