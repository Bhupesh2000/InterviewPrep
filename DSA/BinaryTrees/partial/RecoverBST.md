/*
Assignment 7 Q18
https://leetcode.com/problems/recover-binary-search-tree/description/

You are given the root of a binary search tree (BST), where the values of exactly two nodes of the tree were swapped by mistake. Recover the tree without changing its structure.

Example 1:
Input: root = [1,3,null,null,2]
Output: [3,1,null,null,2]
Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.

Example 2:
Input: root = [3,1,4,null,null,2]
Output: [2,1,4,null,null,3]
Explanation: 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3 makes the BST valid.
 
Constraints:
The number of nodes in the tree is in the range [2, 1000].
-2^31 <= Node.val <= 2^31 - 1
 
Follow up: A solution using O(n) space is pretty straight-forward. Could you devise a constant O(1) space solution?
*/

class Solution {
    void inorder(TreeNode* root, vector<TreeNode*>& nodes) {
        if (!root) return;
        inorder(root->left, nodes);
        nodes.push_back(root);
        inorder(root->right, nodes);
    }

public:
    void recoverTree(TreeNode* root) {
        vector<TreeNode*> nodes;
        inorder(root, nodes);

        TreeNode* first = nullptr;
        TreeNode* second = nullptr;

        for (int i = 0; i < nodes.size() - 1; ++i) {
            if (nodes[i]->val > nodes[i + 1]->val) {
                if (!first) first = nodes[i];         // first anomaly
                second = nodes[i + 1];                 // last anomaly
            }
        }

        if (first && second) {
            swap(first->val, second->val);
        }
    }
};

TC - O(2N), SC - O(N)

--------------------------------------------------------------------------------------------------------------------------------------------

class Solution {
    TreeNode* first = NULL;
    TreeNode* middle = NULL;
    TreeNode* second = NULL;

    void inorder(TreeNode* root, TreeNode* &prev){
        if(!root){
            return;
        }

        inorder(root -> left, prev);
        if(prev && prev -> val > root -> val){
            if(first) second = root;
            else{
                first = prev;
                middle = root;
            }
        }
        prev = root;
        inorder(root -> right, prev);
    }
public:
    void recoverTree(TreeNode* root) {
        TreeNode* prev = NULL;
        inorder(root, prev);
        if(second) swap(first -> val, second -> val);
        else swap(first -> val, middle -> val);
    }
};

TC - O(N), SC - O(1)