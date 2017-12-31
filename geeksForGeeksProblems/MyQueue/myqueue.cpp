#include "myqueue.h"
#include <assert.h>

int MyQueue::peek(){
    assert(!stack1.empty());
    return stack1.top();
}

void MyQueue::dequeue(){
    assert(!stack1.empty());
    stack1.pop();
    size--;
}

void MyQueue::enqueue(int value){
    stack1.push(value);
        while(!stack1.empty()){
            int temp = stack1.top();
            stack1.pop();

            stack2.push(temp);
        }
    intStack temp = stack1;
    stack1 = stack2;
    stack2 =temp;
}
