/*
Assignment 7 Q1
https://leetcode.com/problems/maximum-depth-of-binary-tree/description/

Given the root of a binary tree, return its maximum depth.
A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

Example 1:
Input: root = [3,9,20,null,null,15,7]
Output: 3

Example 2:
Input: root = [1,null,2]
Output: 2
*/

Recursive Solution - 
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        return 1 + max(maxDepth(root -> left), maxDepth(root -> right));
    }
};

Iterative Solution - 
class Solution {
public:
    int maxDepth(TreeNode* root) {
        int depth = 0;
        if(!root) return depth;

        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()){
            int qSize = q.size();
            depth ++;

            for(int i = 1; i <= qSize; i++){
                TreeNode* front = q.front();
                q.pop();
                if(front -> left) q.push(front -> left);
                if(front -> right) q.push(front -> right);
            }
        }

        return depth;

    }
};