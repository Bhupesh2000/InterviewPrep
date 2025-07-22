/*
Assignment 9 Q12
https://practice.geeksforgeeks.org/problems/swap-kth-node-from-beginning-and-kth-node-from-end-in-a-singly-linked-list/1/?track=amazon-linkedlists&batchId=192

A singly linked list and an integer of k are given. You need to swap the kth node from the beginning and the kth node from the end of the linked list. Swap the nodes through the links. Do not change the content of the nodes.
Note: The driver code will output "true" if you successfully swap the nodes.

Examples:
Input: LinkedList: 1->2->3->4, k = 1
Output: true
Explanation: Here k = 1, hence after swapping the 1st node from the beginning and end the new list will be 4->2->3->1. 
Input: LinkedList: 1->2->3->4->5, k = 7
Output: true
Explanation: k > n. Swapping is invalid. Return the head node as it is.

Expected Time Complexity: O(n)
Expected Auxillary Space: O(1)

Constraints:
1 <= number of nodes <= 10^3
1 <= node->data <= 10^6
1 <= k <= 10^3
*/

class Solution {
    int lengthOfLL(Node* head){
        int len = 0;
        Node* temp = head;
        while(temp){
            len ++;
            temp = temp -> next;
        }
        return len;
    }
  public:
    Node* swapKthNode(Node* head, int k) {
        // code here
        int len = lengthOfLL(head);
        if(k > len) return head;
        if(2 * k - 1 == len) return head;
        
        Node dummy(0);
        dummy.next = head;
        
        Node* prev1 = &dummy;
        Node* prev2 = &dummy;
        for(int i = 1; i < k; i++){
            prev1 = prev1 -> next;
        }
        for(int i = 1; i <= len - k; i++){
            prev2 = prev2 -> next;
        }
        
        Node* n1 = prev1 -> next;
        Node* n2 = prev2 -> next;
        
        if(n1 -> next == n2){
            prev1 -> next = n2;
            n1 -> next = n2 -> next;
            n2 -> next = n1;
        }
        else if(n2 -> next == n1){
            prev2 -> next = n1;
            n2 -> next = n1 -> next;
            n1 -> next = n2;
        }
        else{
            Node* nxt = n1 -> next;
            n1 -> next = n2 -> next;
            prev2 -> next = n1;
            prev1 -> next = n2;
            n2 -> next = nxt;
        }
        
        return dummy.next;
    }
};

TC - O(N), SC - O(1)