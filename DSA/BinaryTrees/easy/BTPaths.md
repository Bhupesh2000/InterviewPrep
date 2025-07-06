/*
Assignment 7 Q3
https://leetcode.com/problems/binary-tree-paths/description/

Given the root of a binary tree, return all root-to-leaf paths in any order.
A leaf is a node with no children.

Example 1:
Input: root = [1,2,3,null,5]
Output: ["1->2->5","1->3"]

Example 2:
Input: root = [1]
Output: ["1"]
 
Constraints:
The number of nodes in the tree is in the range [1, 100].
-100 <= Node.val <= 100
*/

class Solution {
    void binaryTreePaths(TreeNode* root, string& current, vector<string>& ans) {
        if (!root) return;

        int len = current.length();  // Save current state for backtracking

        current += to_string(root->val);
        
        if (!root->left && !root->right) {
            ans.push_back(current);
        } else {
            current += "->";
            binaryTreePaths(root->left, current, ans);
            binaryTreePaths(root->right, current, ans);
        }

        current.erase(len);  // Backtrack to previous state
    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        string current;
        vector<string> ans;
        binaryTreePaths(root, current, ans);
        return ans;
    }
};