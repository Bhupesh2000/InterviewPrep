/*
Assignment 7 Q17
https://practice.geeksforgeeks.org/problems/sum-tree/1

Given a Binary Tree. Check for the Sum Tree for every node except the leaf node. Return true if it is a Sum Tree otherwise, return false.
A SumTree is a Binary Tree where the value of a node is equal to the sum of the nodes present in its left subtree and right subtree. An empty tree is also a Sum Tree as the sum of an empty tree can be considered to be 0. A leaf node is also considered a Sum Tree.

Examples:
Input:
    3
  /   \    
 1     2
Output: true
Explanation: The sum of left subtree and right subtree is 1 + 2 = 3, which is the value of the root node. Therefore,the given binary tree is a sum tree.

Input:
          10
        /    \
      20      30
    /   \ 
   10    10
Output: false
Explanation: The given tree is not a sum tree. For the root node, sum of elements in left subtree is 40 and sum of elements in right subtree is 30. Root element = 10 which is not equal to 30+40.

Input:
   25
  /   \    
 9     15
Output: false

Constraints:
2 ≤ number of nodes ≤ 10^5
1 ≤ node->data ≤ 10^5
*/

class Solution {
    pair<long long, bool> isSumTreeHelper(Node* root){
        if(!root){
            return {0, true};
        }
        if(!root -> left && !root -> right) return {root -> data, true};
        pair<long long, bool> leftAns = isSumTreeHelper(root -> left);
        pair<long long, bool> rightAns = isSumTreeHelper(root -> right);
        long long sum = leftAns.first + rightAns.first + root -> data;
        bool isSumTree = (leftAns.first + rightAns.first) == root -> data;
        isSumTree = (isSumTree && leftAns.second) && rightAns.second;
        return {sum, isSumTree};
    }
    
  public:
    bool isSumTree(Node* root) {
        // Your code here
        return isSumTreeHelper(root).second;
    }
};