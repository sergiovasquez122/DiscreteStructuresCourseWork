#include <iostream>
using std::cout;
using std::endl;

struct node{
    node():value(0),next(nullptr){}
    node(int val):value(val),next(nullptr){}
    int value;
    node* next;
};

node* reverse(node* head){
    node* curr = nullptr;
    node* next;
    while(head){
        next= head->next;
        head->next =curr;
        curr = head;
        head = next;
    }
    return curr;
}

node* createNode(int val){
    node* temp = new node(val);
    return temp;
}

node* addNode(node** head,int val){
    node* temp = new node();
    if(!*head){
        *head = temp;
        return *head;
    }
    temp = *head;
    while(temp->next)
        temp = temp->next;
    temp->next = createNode(val);
    return *head;
}

void printList(node* head){
    while(head){
        cout<<head->value<<" ";
        head = head->next;
    }
    cout<<endl;
}

bool isPalindrome(node* head){
    bool palindrome = true;
    node* temp = new node(head->value);
    temp = reverse(head);
    while(head && palindrome){
        palindrome = (head->value==temp->value);
        head= head->next;
        temp = temp->next;
    }
    return palindrome;
}

int main()
{
    node* head = new node(12);
    head = addNode(&head,12);
    head = addNode(&head,12);
    head = addNode(&head,12);
    head = addNode(&head,12);
    cout<<isPalindrome(head)<<endl;
}
