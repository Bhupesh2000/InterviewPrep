/*
https://leetcode.com/problems/binary-tree-right-side-view/submissions/1690860099/

Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

Example 1:
Input: root = [1,2,3,null,5,null,4]
Output: [1,3,4]

Example 2:
Input: root = [1,2,3,4,null,null,null,5]
Output: [1,3,4,5]

Example 3:
Input: root = [1,null,3]
Output: [1,3]

Example 4:
Input: root = []
Output: []

Constraints:
The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100
*/

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        if(!root) return ans;
        queue<TreeNode*> q;
        q.push(root);
        q.push(NULL);
        while(!q.empty()){
            TreeNode* front = q.front();
            q.pop();
            if(front -> left) q.push(front -> left);
            if(front -> right) q.push(front -> right);

            if(!q.empty() && !q.front()){
                ans.push_back(front -> val);
                q.pop();
                if(!q.empty()) q.push(NULL);
            }
        }

        return ans;
    }
};

TC - O(N), SC - (2^h)