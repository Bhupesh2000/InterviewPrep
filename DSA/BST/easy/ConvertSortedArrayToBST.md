/*
Assignment 7 Q4
https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/description/

Given an integer array nums where the elements are sorted in ascending order, convert it to a height-balanced binary search tree.

Example 1:
Input: nums = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]
Explanation: [0,-10,5,null,-3,null,9] is also accepted:

Example 2:
Input: nums = [1,3]
Output: [3,1]
Explanation: [1,null,3] and [3,1] are both height-balanced BSTs.
 
Constraints:
1 <= nums.length <= 10^4
-10^4 <= nums[i] <= 10^4
nums is sorted in a strictly increasing order.
*/

class Solution {
    TreeNode* sortedArrayToBST(vector<int>& nums, int leftIndex, int rightIndex){
        if(leftIndex > rightIndex) return NULL;
        if(leftIndex == rightIndex) return new TreeNode(nums[leftIndex]);

        int mid = leftIndex + (rightIndex - leftIndex) / 2;

        TreeNode* root = new TreeNode(nums[mid]);

        TreeNode* leftChild = sortedArrayToBST(nums, leftIndex, mid - 1);
        TreeNode* rightChild = sortedArrayToBST(nums, mid + 1, rightIndex);

        root -> left = leftChild;
        root -> right = rightChild;

        return root;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedArrayToBST(nums, 0,  nums.size() - 1);
    }
};