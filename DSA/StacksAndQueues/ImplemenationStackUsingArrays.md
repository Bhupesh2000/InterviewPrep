#include <vector>
#include <iostream>
using namespace std;

int SIZE = 100;

template <typename T>
class Stack{
    vector<T> v;
    int front;
    
public:
    Stack(){
        front = -1;
        v.resize(SIZE);
    }
    
    void push(T val){
        if(front == SIZE){
            cout <<"Stack overflow" << endl;
            return;
        }
        front ++;
        v[front] = val;
    }
    
    void pop(){
        if(front == -1){
            cout <<"Stack underflow" << endl;
            return;
        }
        front --;
    }
    
    T top(){
        if(front == -1){
            return -1;
        }
        return v[front];
    }
    
    bool isEmpty(){
        return front == -1;
    }
    
    void display(){
        for(int i = front; i >= 0; i--){
            cout << v[i] << " ";
        }
        cout << endl;
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