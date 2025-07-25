/*
https://leetcode.com/problems/binary-tree-maximum-path-sum/description/

A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.
The path sum of a path is the sum of the node's values in the path.
Given the root of a binary tree, return the maximum path sum of any non-empty path.

Example 1:
Input: root = [1,2,3]
Output: 6
Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.

Example 2:
Input: root = [-10,9,20,null,null,15,7]
Output: 42
Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.
 
Constraints:
The number of nodes in the tree is in the range [1, 3 * 104].
-1000 <= Node.val <= 1000
*/

class Solution {
    int maxPathSum(TreeNode* root, int& maximum){
        if(!root) return 0;
        int leftSum = max(0, maxPathSum(root -> left, maximum));
        int rightSum = max(0, maxPathSum(root -> right, maximum));

        maximum = max(maximum, leftSum + rightSum + root -> val);

        return max(leftSum, rightSum) + root -> val;
    }
public:
    int maxPathSum(TreeNode* root) {
        int maximum = INT_MIN;
        maxPathSum(root, maximum);
        return maximum;
    }
};

Brute force solution will be to get all the paths and there TC - O(N^2)