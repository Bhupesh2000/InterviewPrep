/*
Assignment 9 Q1
https://leetcode.com/problems/palindrome-linked-list/

Given the head of a singly linked list, return true if it is a palindrome or false otherwise.
Example 1:
Input: head = [1,2,2,1]
Output: true

Example 2:
Input: head = [1,2]
Output: false

Constraints:
The number of nodes in the list is in the range [1, 105].
0 <= Node.val <= 9 

Follow up: Could you do it in O(n) time and O(1) space?
*/

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

    ListNode* middleNode(ListNode* head) {
        if(!head || !head -> next) return head;
        ListNode* slow = head;
        ListNode* fast = head -> next;
        while(fast && fast -> next){
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        ListNode* head1 = slow -> next;
        slow -> next = NULL;
        return head1;
    }

public:
    bool isPalindrome(ListNode* head) {
        ListNode* secondHalf = middleNode(head);
        ListNode* reversedSecondHalf = reverseList(secondHalf);

        ListNode* p1 = head;
        ListNode* p2 = reversedSecondHalf;
        while (p2) {
            if (p1->val != p2->val) return false;
            p1 = p1->next;
            p2 = p2->next;
        }
        return true;
    }
};

| Method                         | Time | Space        | Modifies List? | Notes                                   |
| ------------------------------ | ---- | ------------ | -------------- | --------------------------------------- |
| 1. Reverse second half         | O(n) | O(1)         | Yes            | Most optimal in space and time          |
| 2. Copy list to vector/array   | O(n) | O(n)         | No             | Simple, uses extra space                |
| 3. Recursion with two pointers | O(n) | O(n) (stack) | No             | Elegant but not optimal for large lists |
| 4. Push first half to stack    | O(n) | O(n)         | No             | Balanced, non-recursive                 |
