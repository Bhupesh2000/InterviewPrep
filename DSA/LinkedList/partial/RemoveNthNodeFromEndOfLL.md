/*
Assignment 9 Q5
https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/

Given the head of a linked list, remove the nth node from the end of the list and return its head.

Example 1:
Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]

Example 2:
Input: head = [1], n = 1
Output: []

Example 3:
Input: head = [1,2], n = 1
Output: [1]

Constraints:
The number of nodes in the list is sz.
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz

Follow up: Could you do this in one pass?
*/

Approach 1 - Reverse the LL and then delete nth node
Tc - O(N) -> two passes, SC - O(1)

Approach 2 - Find the length of the Linked List and then delete len - nth node
class Solution {
    int lengthofLL(ListNode* head){
        int ans = 0;
        ListNode* temp = head;
        while(temp){
            ans++;
            temp = temp -> next;
        }
        return ans;
    }
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int len = lengthofLL(head);
        n = len - n;
        if(n == 0){
            ListNode* temp = head -> next;
            head -> next = NULL;
            delete head;
            return temp;
        }
        ListNode* temp = head;
        while(n > 1){
            temp = temp -> next;
            n --;
        }
        ListNode* temp2 = temp -> next;
        temp -> next = temp2 -> next;
        temp2 -> next = NULL;
        delete temp2;
        return head;
    }
};

TC - O(N) -> two passes, SC - O(1)

Approach 3 - using 2 pointers.
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* fast = &dummy;
        ListNode* slow = &dummy;
        for(int i = 0; i <= n; i++){
            fast = fast -> next;
        }
        while(fast){
            slow = slow -> next;
            fast = fast -> next;
        }
        ListNode* temp = slow -> next;
        slow -> next = temp -> next;
        temp -> next = NULL;
        delete temp;
        return dummy.next;
    }
};

TC - O(N) -> one pass, SC - O(1).
*** Learn this dummy linkedlist method to handle edge cases related to head

