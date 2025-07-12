/*
https://leetcode.com/problems/symmetric-tree/description/

Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

Example 1:
Input: root = [1,2,2,3,4,4,3]
Output: true

Example 2:
Input: root = [1,2,2,null,3,null,3]
Output: false
 
Constraints:
The number of nodes in the tree is in the range [1, 1000].
-100 <= Node.val <= 100
*/

Recursive Solution -
class Solution {
    bool isSymmetric(TreeNode* p, TreeNode* q){
        if(!p && !q) return true;
        if(!p || !q) return false;

        if(p -> val != q -> val) return false;

        return (isSymmetric(p -> left, q -> right) && isSymmetric(p -> right, q -> left));
    }
public:
    bool isSymmetric(TreeNode* root) {
        if(!root) return true;
        return isSymmetric(root -> left, root -> right);
    }
};

Iterative Solution - 
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(!root) return true;
        queue<TreeNode*> q;
        q.push(root -> left);
        q.push(root -> right);

        while(!q.empty()){
            TreeNode* n1 = q.front();
            q.pop();
            TreeNode* n2 = q.front();
            q.pop();
            if(!n1 && !n2) continue;
            if(!n1 || !n2) return false;
            if(n1 -> val != n2 -> val) return false;
            q.push(n1 -> left);
            q.push(n2 -> right);
            q.push(n1 -> right);
            q.push(n2 -> left);
        }

        return true;
    }
};