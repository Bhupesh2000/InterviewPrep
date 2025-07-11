/*
Assignment 7 Q23
https://leetcode.com/problems/flatten-binary-tree-to-linked-list/

Given the root of a binary tree, flatten the tree into a "linked list":
The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
The "linked list" should be in the same order as a pre-order traversal of the binary tree.
 
Example 1:
Input: root = [1,2,5,3,4,null,6]
Output: [1,null,2,null,3,null,4,null,5,null,6]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [0]
Output: [0]
 
Constraints:
The number of nodes in the tree is in the range [0, 2000].
-100 <= Node.val <= 100
*/

Approach 1 - using a pair

class Solution {
    pair<TreeNode*, TreeNode*> helper(TreeNode* root){
        if(!root) return {NULL, NULL};
        if(!root -> left && !root -> right) return {root, root};

        pair<TreeNode*, TreeNode*> leftAns = helper(root -> left);
        pair<TreeNode*, TreeNode*> rightAns = helper(root -> right);

        root -> left = NULL;

        if(leftAns.first){
            root -> right = leftAns.first;
            leftAns.second -> right = rightAns.first;
        }
        else{
            root -> right = rightAns.first;
        }

        if(rightAns.second) return {root, rightAns.second};
        else return {root, leftAns.second};
    }
public:
    void flatten(TreeNode* root) {
        helper(root);
    }
};

TC - O(N), SC - O(N)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - using a prev pointer

class Solution {
    TreeNode* prev = NULL;
public:
    void flatten(TreeNode* root) {
        if(!root) return;
        flatten(root -> right);
        flatten(root -> left);
        root -> right = prev;
        root -> left = NULL;
        prev = root;
    }
};

TC - O(N), SC - O(N)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 3 - level order, using stack

class Solution {
public:
    void flatten(TreeNode* root) {
        if(!root) return;
        stack<TreeNode*> st;
        st.push(root);
        while(!st.empty()){
            TreeNode* top = st.top();
            st.pop();
            if(top -> right) st.push(top -> right);
            if(top -> left) st.push(top -> left);

            if(!st.empty()) top -> right = st.top();
            top -> left = NULL;
        }
    }
};

TC - O(N), SC - O(N)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 4 - Morris Traversal

class Solution {
public:
    void flatten(TreeNode* root) {
        if(!root) return;
        TreeNode* curr = root;
        while(curr){
            if(curr -> left){
                TreeNode* prev = curr -> left;
                while(prev -> right) prev = prev -> right;
                prev -> right = curr -> right;
                curr -> right = curr -> left;
                curr -> left = NULL;
            }
            curr = curr -> right;
        }
    }
};

TC - O(N), SC - O(1)
