/*
Assignment 7 Q7
https://leetcode.com/problems/minimum-absolute-difference-in-bst/description/

Given the root of a Binary Search Tree (BST), return the minimum absolute difference between the values of any two different nodes in the tree.

Example 1:
Input: root = [4,2,6,1,3]
Output: 1

Example 2:
Input: root = [1,0,48,null,null,12,49]
Output: 1
 
Constraints:
The number of nodes in the tree is in the range [2, 104].
0 <= Node.val <= 105
*/

Approach 1 - Inorder traversal of BST will always result in a sorted array.
class Solution {
    void inorderTraversal(TreeNode* root, vector<int>& inorder){
        if(!root) return;
        inorderTraversal(root -> left, inorder);
        inorder.push_back(root -> val);
        inorderTraversal(root -> right, inorder);
    }
public:
    int getMinimumDifference(TreeNode* root) {
        vector<int> inOrder;
        inorderTraversal(root, inOrder);
        int minDiff = INT_MAX;
        for(int i = 1; i < inOrder.size(); i++){
            minDiff = min(minDiff, inOrder[i] - inOrder[i - 1]);
        }
        return minDiff;
    }
};

TC - O(N) -> populating inOrder array + O(N) -> finding the minDiff, SC - O(h) -> recursion stack + O(N) -> vector

Approach 2 - Using prev pointer instead of storing all the values in extra vector
class Solution {
    void getMinimumDifference(TreeNode* root, TreeNode* &prev, int& minDiff){
        if(!root) return;
        getMinimumDifference(root -> left, prev, minDiff);
        if(prev) minDiff = min(minDiff, root -> val - prev -> val);
        prev = root;
        getMinimumDifference(root -> right, prev, minDiff);
    }
public:
    int getMinimumDifference(TreeNode* root) {
        int minDiff = INT_MAX;
        TreeNode* prev = NULL;
        getMinimumDifference(root, prev, minDiff);
        return minDiff;
    }
};

TC - O(N), SC - O(h)