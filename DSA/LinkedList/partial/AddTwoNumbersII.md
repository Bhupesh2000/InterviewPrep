/*
Assignment 9 Q13
https://leetcode.com/problems/add-two-numbers-ii/

You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.
You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example 1:
Input: l1 = [7,2,4,3], l2 = [5,6,4]
Output: [7,8,0,7]

Example 2:
Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [8,0,7]

Example 3:
Input: l1 = [0], l2 = [0]
Output: [0]
 
Constraints:
The number of nodes in each linked list is in the range [1, 100].
0 <= Node.val <= 9
It is guaranteed that the list represents a number that does not have leading zeros.
 
Follow up: Could you solve it without reversing the input lists?
*/

Approach 1 - using 2 vectors and storing the values of both linked lists in the vectors and then adding
TC - O(N), SC - O(N)

Approch 2 - reversing the linked lists and then adding from start
class Solution {
    ListNode* reverseList(ListNode* head) {
        if(!head || !head -> next) return head;
        ListNode* prev = NULL;
        ListNode* curr = head;
        ListNode* nxt = head -> next;
        while(nxt){
            curr -> next = prev;
            prev = curr;
            curr = nxt;
            nxt = nxt -> next;
        }
        curr -> next = prev;
        return curr;
    }
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        l1 = reverseList(l1);
        l2 = reverseList(l2);
        ListNode* head = NULL;
        ListNode* tail = NULL;
        ListNode* temp1 = l1;
        ListNode* temp2 = l2;
        int carry = 0;
        while(temp1 && temp2){
            int val = temp1 -> val + temp2 -> val + carry;
            ListNode* newNode = new ListNode(val % 10);
            if(!head) head = newNode;
            else tail -> next = newNode;
            tail = newNode;
            carry = val / 10;
            temp1 = temp1 -> next;
            temp2 = temp2 -> next;
        }
        if(temp1){
            while(temp1){
                int val = temp1 -> val + carry;
                ListNode* newNode = new ListNode(val % 10);
                if(!head) head = newNode;
                else tail -> next = newNode;
                tail = newNode;
                carry = val / 10;
                temp1 = temp1 -> next;
            }
        }
        else{
            while(temp2){
                int val = temp2 -> val + carry;
                ListNode* newNode = new ListNode(val % 10);
                if(!head) head = newNode;
                else tail -> next = newNode;
                tail = newNode;
                carry = val / 10;
                temp2 = temp2 -> next;
            }
        }
        if(carry != 0){
            ListNode* newNode = new ListNode(carry);
            if(!head) head = newNode;
            else tail -> next = newNode;
        }
        return reverseList(head);
    }
};

TC - O(N), SC - O(1)

Approach 3 - using recursion
Add 0s to start of shorter ll to make the size of both lls same
Then call recursively on next nodes of the both lls.
TC - O(N), SC - O(N) -> recursive stack

| Approach             | Time | Space | Notes                                        |
| -------------------- | ---- | ----- | -------------------------------------------- |
| Reverse Both Lists   | O(N) | O(1)  | Requires modifying input or reversing copies |
| Stack / Vector       | O(N) | O(N)  | Easy, safe, no mutation                      |
| Recursion w/ Padding | O(N) | O(N)  | Elegant, no reversal, uses recursion stack   |
