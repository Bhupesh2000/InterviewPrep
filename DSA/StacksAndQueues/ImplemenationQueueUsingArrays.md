#include <vector>
#include <iostream>
using namespace std;

class Queue{
    vector<int> v;
    int frontIndex;
    
public:
    Queue(){
        frontIndex = 0;
    }
    
    void push(int val){
        v.push_back(val);
    }
    
    void pop(){
        if(isEmpty()){
            cout << "Queue underflow" << endl;
            return;
        }
        frontIndex ++;
        if(v.size() / 2 < frontIndex){
            v.erase(v.begin(), v.begin() + frontIndex);
            frontIndex = 0;
        }
    }
    
    int front(){
        if(isEmpty()) return -1;
        return v[frontIndex];
    }
    
    bool isEmpty(){
        return v.size() <= frontIndex;
    }
    
    int size(){
        return v.size() - frontIndex;
    }
    
    void display() {
        for (int i = frontIndex; i < v.size(); ++i) {
            cout << v[i] << " ";
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
    cout << q.size() << endl;   // 2

    q.pop(); q.pop();
    q.pop();  // Queue underflow


    return 0;
}