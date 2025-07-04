/*
Assignment 6 Q12
https://leetcode.com/problems/implement-stack-using-queues/description/

Implement a last-in-first-out (LIFO) stack using only two queues. The implemented stack should support all the functions of a normal stack (push, top, pop, and empty).

Implement the MyStack class:

void push(int x) Pushes element x to the top of the stack.
int pop() Removes the element on the top of the stack and returns it.
int top() Returns the element on the top of the stack.
boolean empty() Returns true if the stack is empty, false otherwise.
Notes:

You must use only standard operations of a queue, which means that only push to back, peek/pop from front, size and is empty operations are valid.
Depending on your language, the queue may not be supported natively. You may simulate a queue using a list or deque (double-ended queue) as long as you use only a queue's standard operations.
 
Example 1:
Input
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
Output
[null, null, null, 2, 2, false]

Explanation
MyStack myStack = new MyStack();
myStack.push(1);
myStack.push(2);
myStack.top(); // return 2
myStack.pop(); // return 2
myStack.empty(); // return False
 
Constraints:

1 <= x <= 9
At most 100 calls will be made to push, pop, top, and empty.
All the calls to pop and top are valid.
*/

Implementation using 2 queues - 

class MyStack {
    queue<int> q1;
    queue<int> q2;
public:
    MyStack() {
    }
    
    void push(int x) {
        q2.push(x);
        while(!q1.empty()){
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);
    }
    
    int pop() {
        int a = q1.front();
        q1.pop();
        return a;
    }
    
    int top() {
        return q1.front();
    }
    
    bool empty() {
        return q1.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

| Operation  | Time Complexity                          | Space Complexity     |
| ---------- | ---------------------------------------- | -------------------- |
| `push(x)`  | Worst: **O(n)** per op, Total: **O(q²)** | —                    |
| `pop()`    | **O(1)**                                 | —                    |
| `top()`    | **O(1)**                                 | —                    |
| `empty()`  | **O(1)**                                 | —                    |
| Overall SC | —                                        | **O(n)**             |


--------------------------------------------------------------------------------------------------------------------------------------------

Implementation using 1 queue

class MyStack {
    queue<int> q;
    void reverseQueue(){
        if(q.empty()) return;
        int frontElement = q.front();
        q.pop();
        reverseQueue();
        q.push(frontElement);
    }
public:
    MyStack() {
    }
    
    void push(int x) {
        q.push(x);
        reverseQueue();
    }
    
    int pop() {
        int frontElement = q.front();
        q.pop();
        return frontElement;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

TC and SC will same as 2 queues.
SC earlier was from using 2 queues. Now from 1 queue + recursion stack.

Comparison table :

| Feature            | 2-Queue Version  | Recursive Version          |
| ------------------ | ---------------- | -------------------------- |
| `push(x)` Time     | O(n)             | O(n)                       |
| Total Time (q ops) | O(q²)            | O(q²)                      |
| Space Used         | O(n) (2 queues)  | O(n) (1 queue + recursion) |
| Extra Overhead     | Uses extra queue | Uses call stack            |
