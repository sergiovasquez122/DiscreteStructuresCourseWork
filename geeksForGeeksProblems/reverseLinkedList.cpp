//Reverse the content of a linked list
#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    Node(int init) {data=init;}
    int data;
    Node* next = nullptr;
};

void printNodes(Node* head) {
    Node* tmp = head;
    while (tmp!=nullptr) {
        cout << tmp->data;
        tmp = tmp->next;
    }
    cout<<endl;
}

// Passing pointer to pointer to head
void addNodeToEnd(Node** head, int data) {
    if (*head==nullptr) {
        *head = new Node(data);
        return;
    }
    Node* tmp = *head;
    while (tmp->next != nullptr) {
        tmp = tmp->next;
    }
    tmp->next = new Node(data);
}

void addNodeToHead(Node** head) {
    Node* tmp = new Node(0);
    tmp->next = *head;
    *head = tmp;
    printNodes(*head);
}

void deleteNode(Node** head) {
    deleteNode(&((*head)->next));
    delete(*head);
    printNodes(*head);
}

void reverseList(Node** head) {
    Node* previous = nullptr;
    Node* next = nullptr;
    Node* current = *head;
    // previous -> current -> next
    while (current != nullptr) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    *head = previous;
    printNodes(*head);
}

int main() {

    Node* head = nullptr;

    // create linked list of 3 nodes
    for (int i=0; i<3; i++)
        addNodeToEnd(&head, i+1);

    // print the linked list
    printNodes(head);

    // add node to front
    addNodeToHead(&head);

    // reverse list
    reverseList(&head);

    return 0;
}

