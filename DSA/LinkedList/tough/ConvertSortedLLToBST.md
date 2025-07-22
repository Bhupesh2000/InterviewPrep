/*
Assignment 9 Q14
https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree

Given the head of a singly linked list where elements are sorted in ascending order, convert it to a height-balanced binary search tree.

Example 1:
Input: head = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]
Explanation: One possible answer is [0,-3,9,-10,null,5], which represents the shown height balanced BST.

Example 2:
Input: head = []
Output: []
 
Constraints:
The number of nodes in head is in the range [0, 2 * 10^4].
-10^5 <= Node.val <= 10^5
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

Approach 1 - find mid and call for left and right child
class Solution {
    ListNode* findMidPrev(ListNode* head){
        ListNode* slow = head;
        ListNode* fast = head -> next -> next;
        while(fast && fast -> next){
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        return slow;
    }
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if(!head) return NULL;
        if(!head -> next) return new TreeNode(head -> val);

        ListNode* midPrev = findMidPrev(head);

        ListNode* root = midPrev -> next;
        ListNode* rightHead = root -> next;

        midPrev -> next = NULL;
        root -> next = NULL;

        TreeNode* leftChild = sortedListToBST(head);
        TreeNode* rightChild = sortedListToBST(rightHead);

        TreeNode* rootNode = new TreeNode(root -> val);
        rootNode -> left = leftChild;
        rootNode -> right = rightChild;

        midPrev -> next = root;
        root -> next = rightHead;

        return rootNode;
    }
};

SC - O(logN) -> recursive tree(height of height balanced tree), 
TC - O(NlogN)
Finding the middle takes O(n) in the worst case (because it’s a singly-linked list — no random access).
You do this log n times due to the recursive tree depth (balanced binary tree depth ≈ log n).
T(n) = O(n) + 2 * T(n/2) = O(n log n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - copy the ll into a vector and then find mid in O(1) and call upon left and right child
TC - O(N), SC - O(N)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 3 - Simulated Inorder Construction
Simulate in-order traversal of BST while consuming the list in order.
Count the length of the list first.
Use recursion to build left subtree of size n/2, then root, then right subtree.

class Solution {
    ListNode* current;

    TreeNode* buildBST(int left, int right) {
        if (left > right) return nullptr;

        int mid = (left + right) / 2;
        TreeNode* leftChild = buildBST(left, mid - 1);

        TreeNode* root = new TreeNode(current->val);
        root->left = leftChild;
        current = current->next;

        root->right = buildBST(mid + 1, right);
        return root;
    }

    int getLength(ListNode* head) {
        int len = 0;
        while (head) {
            len++;
            head = head->next;
        }
        return len;
    }

public:
    TreeNode* sortedListToBST(ListNode* head) {
        int len = getLength(head);
        current = head;
        return buildBST(0, len - 1);
    }
};

TC - O(N), SC - O(logN)

--------------------------------------------------------------------------------------------------------------------------------------------

| Approach                        | Time       | Space    | Notes                                |
| ------------------------------- | ---------- | -------- | ------------------------------------ |
| 1. Mid Recursion                | O(n log n) | O(log n) | Classic and intuitive                |
| 2. Copy to Array                | O(n)       | O(n)     | Simple to code, extra space required |
| 3. Inorder Simulation (Optimal) | **O(n)**   | O(log n) | Best overall – avoids slicing        |
