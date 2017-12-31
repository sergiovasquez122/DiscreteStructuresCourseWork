//implement a queue using two stacks
#include <iostream>
#include "myqueue.h"
using namespace std;

int main()
{
    MyQueue testStack;
    testStack.enqueue(12);
    testStack.enqueue(69);
    cout<<testStack.peek()<<endl;
    testStack.dequeue();
    cout<<testStack.peek()<<endl;
    testStack.dequeue();
}
