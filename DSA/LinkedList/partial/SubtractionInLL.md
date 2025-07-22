/*
Assignment 9 Q15
https://practice.geeksforgeeks.org/problems/subtraction-in-linked-list/1/?track=amazon-linkedlists&batchId=192

You are given two linked lists representing two large positive numbers. The linked lists represent these two numbers, subtract the smaller number from the larger one and return the head of the linked list representing the result. Please take a look at the examples to get a better understanding of the task.
The linked list does not contain leading zeros, except for the number zero itself.

Examples:
Input: LinkedList1: 1->0->0, LinkedList2: 1->2
Output:  LinkedList: 8->8
Explanation: First linked list represents 100 and the second one represents 12. 12 subtracted from 100 gives us 88 as the result. It is represented as 8->8 in the linked list.

Input: LinkedList1: 6->3, LinkedList2: 7->1->0
Output: LinkedList: 6->4->7
Explanation: First linked list represents 63 and the second one represents 710. 63 subtracted from 710 gives us 647 as the result. It is represented as 6->4->7 in the linked list.

Constraints:
1 <= size of both linked lists <= 10^6
0 <= node->data <= 9
*/

Approach 1 - Iterative method(by reversing the linked lists)
class Solution {
    Node* getLargerNumber(Node* head1, Node* head2){
        Node* temp1 = head1;
        Node* temp2 = head2;
        Node* largerHead = NULL;
        while(temp1 && temp2){
            if(temp1 -> data > temp2 -> data && !largerHead){
                largerHead = head1;
            }
            else if(temp2 -> data > temp1 -> data && !largerHead){
                largerHead = head2;
            }
            temp1 = temp1 -> next;
            temp2 = temp2 -> next;
        }
        if(!temp1 && !temp2){
            if(largerHead) return largerHead;
            else return head1;
        }
        else if(!temp1) return head2;
        else return head1;
        
    }
    
    Node* reverseLL(Node* head){
        if(!head || !head -> next) return head;
        Node* prev = NULL;
        Node* curr = head;
        Node* nxt = head -> next;
        while(nxt){
            curr -> next = prev;
            prev = curr;
            curr = nxt;
            nxt = nxt -> next;
        }
        curr -> next = prev;
        return curr;
    }
    
    Node* removeLeadingZeroes(Node* head){
        Node* temp = head;
        while(temp && temp -> data == 0){
            head = head -> next;
            temp -> next = NULL;
            delete temp;
            temp = head;
        }
        if(!head) return new Node(0);
        return head;
    }
    
  public:
    Node* subLinkedList(Node* head1, Node* head2) {
        // Your implementation of subLinkedList goes here
        // Make sure to return the head of the resulting linked list
        Node* h1 = getLargerNumber(head1, head2);
        Node* h2 = (h1 == head1) ? head2 : head1;
        
        h1 = reverseLL(h1);
        h2 = reverseLL(h2);
        
        Node* temp1 = h1;
        Node* temp2 = h2;
        
        Node* head = NULL;
        Node* tail = NULL;
        
        bool carry = false;
        while(temp1 && temp2){
            int a = temp1 -> data;
            int b = temp2 -> data;
            if(carry) a --;
            int data = a - b;
            if(data < 0){
                data = 10 + data;
                carry = true;
            }
            else carry = false;
            Node* newNode = new Node(data);
            if(!head) head = newNode;
            else tail -> next = newNode;
            tail = newNode;
            temp1 = temp1 -> next;
            temp2 = temp2 -> next;
        }
        
        if(temp1){
            if(!head) return reverseLL(h1);
            while(temp1){
                int a = temp1 -> data;
                if(carry){
                   a --;
                   if(a < 0) a = 10 + a;
                   else carry = false;
                }
                Node* newNode = new Node(a);
                tail -> next = newNode;
                tail = newNode;
                temp1 = temp1 -> next;
            }
        }
        head = reverseLL(head);
        return removeLeadingZeroes(head);
    }
};

TC - O(4 N), SC - O(N)

Approach 2 - using recursion (top to down)
TC = O(N), SC - O(N)

Approach 3 - convert to string/integer
TC - O(N), SC - O(N)
converting to integer won't work for very large inputs

| Approach                       | Time Complexity | Space Complexity | In-place | Suitable for Interviews        |
| ------------------------------ | --------------- | ---------------- | -------- | ------------------------------ |
| Iterative + Reverse            | O(4N)           | O(1)             | ✅        | ✅✅✅                            |
| Recursive                      | O(N)            | O(N)             | ❌        | ✅✅✅✅ (shows recursion skills)  |
| Convert to Int/String and Back | O(N)            | O(N)             | ❌        | ✅ (if allowed, less preferred) |
