#include <iostream>
using namespace std;

template <typename T>
class Node{
public:
    T val;
    Node* next;
    
    Node(T val){
        this -> val = val;
        next = NULL;
    }
};

template <typename T>
class Stack{
    Node<T>* head;
    int size;
    
public:
    Stack(){
        head = NULL;
        size = 0;
    }
    
    void push(T val){
        Node<T>* newNode = new Node<T>(val);
        newNode -> next = head;
        head = newNode;
        size ++;
    }
    
    void pop(){
        if(!head){
            cout << "Stack underflow" << endl;
            return;
        }
        Node<T>* temp = head;
        head = head -> next;
        temp -> next = NULL;
        delete temp;
        size --;
    }
    
    bool isEmpty(){
        return size == 0;
    }
    
    int stackSize(){
        return size;
    }
    
    void display(){
        Node<T>* temp = head;
        while(temp){
            cout << temp -> val << " ";
            temp = temp -> next;
        }
    }
    
    T top() {
        if (head) {
            return head->val;
        } else {
            throw runtime_error("Stack is empty");
        }
    }
};

int main() {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    s.display();
    s.pop();
    cout << s.top() << endl;
    cout << s.isEmpty() << endl;
    s.pop();
    s.pop();
    s.pop();
    cout << s.top() << endl;

    return 0;
}