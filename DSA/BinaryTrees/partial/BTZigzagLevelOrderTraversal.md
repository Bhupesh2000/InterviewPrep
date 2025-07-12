/*
https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/

Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).

Example 1:
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[20,9],[15,7]]

Example 2:
Input: root = [1]
Output: [[1]]

Example 3:
Input: root = []
Output: []

Constraints:
The number of nodes in the tree is in the range [0, 2000].
-100 <= Node.val <= 100
*/

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(!root) return ans;
        bool isLeftToRight = true;
        queue<TreeNode* > q;
        q.push(root);
        while(!q.empty()){
            int qSize = q.size();
            vector<int> level(qSize);
            for(int i = 0; i < qSize; i++){
                TreeNode* front = q.front();
                q.pop();
                if(front -> left) q.push(front -> left);
                if(front -> right) q.push(front -> right);
                if(isLeftToRight) level[i] = front -> val;
                else level[qSize - i - 1] = front -> val;
            }
            isLeftToRight = !isLeftToRight;
            ans.push_back(level);
        }
        return ans;
    }
};