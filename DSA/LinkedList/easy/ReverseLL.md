/*
Assignment 9 Q3
https://leetcode.com/problems/reverse-linked-list/

Given the head of a singly linked list, reverse the list, and return the reversed list.

Example 1:
Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]

Example 2:
Input: head = [1,2]
Output: [2,1]

Example 3:
Input: head = []
Output: []

Constraints:
The number of nodes in the list is the range [0, 5000].
-5000 <= Node.val <= 5000
 
Follow up: A linked list can be reversed either iteratively or recursively. Could you implement both?
*/


Approach 1 - Recursive Solution
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head || !head -> next) return head;
        ListNode* newHead = reverseList(head -> next);
        head -> next -> next = head;
        head -> next = NULL;
        return newHead;
    }
};

TC - O(N), SC - O(N) -> recursive stack

Approach 2 - Iterative Solution

class Solution {
public:
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
};

TC - O(N), SC - O(1)