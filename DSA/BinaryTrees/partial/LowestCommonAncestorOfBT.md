/*
https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.

Example 2:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.

Example 3:
Input: root = [1,2], p = 1, q = 2
Output: 1
 
Constraints:
The number of nodes in the tree is in the range [2, 10^5].
-10^9 <= Node.val <= 10^9
All Node.val are unique.
p != q
p and q will exist in the tree.
*/

Approach 1 - generating paths for both the nodes and then comparing
class Solution {
    bool rootToNodePath(TreeNode* root, TreeNode* p, vector<TreeNode*>& path){
        if(!root) return false;
        path.push_back(root);
        if(root == p) return true;
        if(rootToNodePath(root -> left, p, path) || rootToNodePath(root -> right, p, path)) return true;
        path.pop_back();
        return false;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> path1, path2;
        rootToNodePath(root, p, path1);
        rootToNodePath(root, q, path2);
        TreeNode* ans;
        for(int i = 0; i < path1.size() && i < path2.size(); i++){
            if(path1[i] == path2[i]) ans = path1[i];
        }
        return ans;
    }
};

TC - O(2 * N) -> for getting paths + O(N) -> for getting the ans
SC - O(2 * N) -> for path vectors + O(h) -> recursion stack

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - not using any extra space
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return NULL;
        if(root == p || root == q) return root;
        TreeNode* leftAns = lowestCommonAncestor(root -> left, p, q);
        TreeNode* rightAns = lowestCommonAncestor(root -> right, p, q);

        if(!leftAns) return rightAns;
        else if(!rightAns) return leftAns;
        else return root;
    }
};
TC - O(N)
SC - O(h)