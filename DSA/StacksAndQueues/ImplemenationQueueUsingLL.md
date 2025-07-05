#include <iostream>
using namespace std;

class Node{
public:
    int val;
    Node* next;
    Node(int val){
        this -> val = val;
        next = NULL;
    }
};

class Queue{
    Node* head;
    Node* tail;
    int size;
    
public:
    Queue(){
        head = NULL;
        tail = NULL;
        size = 0;
    }
    
    void push(int val){
        Node* newNode = new Node(val);
        if(!head) head = newNode;
        else tail -> next = newNode;
        tail = newNode;
        size++;
    }
    
    void pop(){
        if(!head){
            cout << "Queue underflow" << endl;
            return;
        }
        size --;
        Node* temp = head;
        head = head -> next;
        temp -> next = NULL;
        delete temp;
        if(!head) tail = NULL;
    }
    
    int front(){
        if(!head) return -1;
        return head -> val;
    }
    
    bool isEmpty(){
        return !head;
    }
    
    int getSize(){
        return this -> size;
    }
    
    void display() {
        Node* temp = head;
        while(temp){
            cout << temp -> val << " ";
            temp = temp -> next;
        }
        cout << endl;
    }
};

int main() {
    Queue q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.display();        // 10 20 30

    q.pop();
    q.display();        // 20 30

    cout << q.front() << endl;  // 20
    cout << q.getSize() << endl;   // 2

    q.pop(); 
    q.pop();
    q.pop();  // Queue underflow


    return 0;
}