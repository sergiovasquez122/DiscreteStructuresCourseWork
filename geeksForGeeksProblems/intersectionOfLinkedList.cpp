//find intersection of a linked list
#include <iostream>

using namespace std;

struct node{
    node():data(0),next(nullptr){}
    node(const int val):data(val),next(nullptr){}
    void setLink(node *temp){next=temp;}
    int data;
    node* next;
};

void addToEnd(node** head,int value){
    node* temp = new node(value);
    if(*head){
        node* last = *head;
        while(last->next)
            last = last->next;
        last->next = temp;
    }
    else{
        temp->next = *head;
        *head = temp;
    }
}

void insertNewHead(node**head,int value){
    node* temp = new node(value);
    temp->next = *head;
    *head = temp;
}

void printList(node* head){
    while(head){
        cout<<head->data<<" ";
        head = head->next;
    }
    cout<<endl;
}

int length(node* head){
    int counter = 0;
    while(head){
        counter++;
        head = head->next;
    }
    return counter;
}

//Assuming that both heads are not equal to null;
node* findIntersection(node* head1,node* head2){
    int head1Length = length(head1);
    int head2length = length(head2);
    if(head1Length<head2length){
        node* temp = head1;
        head1= head2;
        head2 =temp;
    }
    while(head1Length!=head2length){
        head1= head1->next;
        head1Length--;
    }

    while((head1!=head2)||head1){
        if(head1=head2)
            return head1;
        head1 = head1->next;
        head2 = head2->next;
    }
    return nullptr;
}

using nodePtr =  node*;

int main()
{
    nodePtr a = new node,b = new node,c = new node, d = new node,f = new node;
    a->setLink(b),b->setLink(c),c->setLink(d);
    f->setLink(b),b->setLink(c),c->setLink(d);
    cout<<b<<endl;
    cout<<findIntersection(a,f)<<endl;
}

