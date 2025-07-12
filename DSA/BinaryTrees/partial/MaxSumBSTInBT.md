/*
Assignment 7 Q21
https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/

Given a binary tree root, return the maximum sum of all keys of any sub-tree which is also a Binary Search Tree (BST).

Assume a BST is defined as follows:
The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.

Example 1:
Input: root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
Output: 20
Explanation: Maximum sum in a valid Binary search tree is obtained in root node with key equal to 3.

Example 2:
Input: root = [4,3,null,1,2]
Output: 2
Explanation: Maximum sum in a valid Binary search tree is obtained in a single root node with key equal to 2.

Example 3:
Input: root = [-4,-2,-5]
Output: 0
Explanation: All values are negatives. Return an empty BST.
 
Constraints:
The number of nodes in the tree is in the range [1, 4 * 104].
-4 * 10^4 <= Node.val <= 4 * 10^4
*/

Approach 1
class Solution {
    pair<bool, pair<int, int>> isValidBST(TreeNode* root, int minV, int maxV){
        if(!root) return {true, {0, 0}};
        if(root -> val <= minV || root -> val >= maxV) return {false, {0, 0}};

        pair<bool, pair<int, int>> p;

        pair<bool, pair<int, int>> left = isValidBST(root -> left, minV, root -> val);
        pair<bool, pair<int, int>> right = isValidBST(root -> right, root -> val, maxV);

        if (!left.first || !right.first) return {false, {0, 0}};

        int currSum = root -> val + left.second.first + right.second.first;

        int maxSubTreeSum = max(currSum, max(left.second.second, right.second.second));

        return {true, {currSum, maxSubTreeSum}};
    }

    void helper(TreeNode* root, int& maxSum){
        if(!root) return;
        pair<bool, pair<int, int>> p = isValidBST(root, INT_MIN, INT_MAX);
        if(p.first){
            maxSum = max(p.second.second, maxSum);
            return;
        }
        helper(root -> left, maxSum);
        helper(root -> right, maxSum);
    }
public:
    int maxSumBST(TreeNode* root) {
        int maxSum = INT_MIN;
        helper(root, maxSum);
        return maxSum;
    }
};

TC - O(N^2), SC - O(h)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2

class Solution {
    struct Info{
        bool isBST;
        int minV;
        int maxV;
        int currSum;
    };

    int maxSum;

    Info dfs(TreeNode* root){
        if(!root) return {true, INT_MAX, INT_MIN, 0};

        Info left = dfs(root -> left);
        Info right = dfs(root -> right);

        Info curr;

        if(left.isBST && right.isBST && root -> val > left.maxV && root -> val < right.minV){
            curr.isBST = true;
            curr.minV = (left.minV != INT_MAX) ? left.minV : root -> val;
            curr.maxV = (right.maxV != INT_MIN) ? right.maxV : root -> val;
            curr.currSum = root -> val + left.currSum + right.currSum;
        }
        else{
            curr.isBST = false;
            curr.minV = INT_MAX;
            curr.maxV = INT_MIN;
            curr.currSum = 0;
        }

        maxSum = max(maxSum, curr.currSum);
        return curr;
    }

public:
    int maxSumBST(TreeNode* root) {
        maxSum = 0;
        dfs(root);
        return maxSum;
    }
};

TC - O(N), SC - O(h)