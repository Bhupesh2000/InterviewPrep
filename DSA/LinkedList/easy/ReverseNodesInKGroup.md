/*
Assignment 9 Q6
https://leetcode.com/problems/reverse-nodes-in-k-group/description/

Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.
k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.
You may not alter the values in the list's nodes, only nodes themselves may be changed.

Example 1:
Input: head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]

Example 2:
Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]

Constraints:
The number of nodes in the list is n.
1 <= k <= n <= 5000
0 <= Node.val <= 1000

Follow-up: Can you solve the problem in O(1) extra memory space?
*/

Approach 1 - Using an extra vector
TC - O(N), SC - O(N)

Approach 2 -
class Solution {
    void reverseList(ListNode* head) {
        if(!head || !head -> next) return;
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
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(k == 1 || !head || !head -> next) return head;
        ListNode* temp = head;
        ListNode* prev = NULL;
        ListNode* nxt = NULL;
        while(temp){
            int n = 1;
            ListNode* currHead = temp;
            while(temp -> next && n < k){
                temp = temp -> next;
                n ++;
            }
            if(n < k){
                if(!prev) head = currHead;
                else prev -> next = currHead;
                break;
            }
            nxt = temp -> next;
            temp -> next = NULL;
            reverseList(currHead);
            if(!prev) head = temp;
            else prev -> next = temp;
            prev = currHead;
            temp = nxt;
        }
        return head;
    }
};

TC - O(N), SC - O(1)