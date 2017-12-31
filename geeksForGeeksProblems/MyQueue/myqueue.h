#ifndef MYQUEUE_H
#define MYQUEUE_H
#include <stack>
using intStack  = std::stack<int>;
using size_type = std::size_t;
class MyQueue
{
public:
    MyQueue():size(0){}
    void enqueue(int value);
    void dequeue();
    int peek();
    size_type Size(){return size;}
private:
    intStack stack1;
    intStack stack2;
    size_type size;
};

#endif // MYQUEUE_H
