/*
Given the root of a binary tree, return the length of the diameter of the tree.
The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.
The length of a path between two nodes is represented by the number of edges between them.

Example 1:
Input: root = [1,2,3,4,5]
Output: 3
Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].

Example 2:
Input: root = [1,2]
Output: 1
 
Constraints:
The number of nodes in the tree is in the range [1, 104].
-100 <= Node.val <= 100
*/


// Brute Force Solution

class Solution {
    int findHeight(TreeNode* root){
        if(!root) return 0;
        return 1 + max(findHeight(root -> left), findHeight(root -> right));
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if(!root) return 0;
        int lH = 0, rH = 0;
        if(root -> left) lH = findHeight(root -> left);
        if(root -> right) rH = findHeight(root -> right);

        int leftD = diameterOfBinaryTree(root -> left);
        int rightD = diameterOfBinaryTree(root -> right);

        return max(lH + rH, max(leftD, rightD));
    }
};

TC - O(N^2), SC - O(h)

// Calculating height and maximum in the same traversal
class Solution {
    int findHeight(TreeNode* root, int& maxi){
        if(!root) return 0;
        int lH = findHeight(root -> left, maxi);
        int rH = findHeight(root -> right, maxi);

        maxi = max(maxi, lH + rH);

        return 1 + max(lH, rH);
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int maximum = 0;
        findHeight(root, maximum);
        return maximum;
    }
};

TC - O(N), SC - O(h)
