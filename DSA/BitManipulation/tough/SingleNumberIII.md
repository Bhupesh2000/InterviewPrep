/*
Assignment 10 Q13
https://leetcode.com/problems/single-number-iii/

Given an integer array nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once. You can return the answer in any order.
You must write an algorithm that runs in linear runtime complexity and uses only constant extra space.

Example 1:
Input: nums = [1,2,1,3,2,5]
Output: [3,5]
Explanation:  [5, 3] is also a valid answer.

Example 2:
Input: nums = [-1,0]
Output: [-1,0]

Example 3:
Input: nums = [0,1]
Output: [1,0]
 
Constraints:
2 <= nums.length <= 3 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
Each integer in nums will appear twice, only two integers will appear once.
*/

Approach 1 - Brute force(checking for each element)
TC - O(N^2), SC - O(1)

Approach 2 - sort and then check
TC - O(NlogN), SC - O(1)

Approach 3 - use hashmap
TC - O(N), SC - O(N)

Approach 4 - bit manipulation
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int n = nums.size();
        int XORR = 0;
        for(int i = 0; i < n; i++){
            XORR ^= nums[i]; // after whole traversal XORR will XORR of both distinct numbers
        }
        // Now since there are 2 distinct numbers. Atleast one bit will be different for both
        // That distinct bits will be represent as set in XORR
        // Convert XORR such that except right most set bit(distinct bit) all the bits are unset
        // int rightMost = (XORR & (XORR - 1)) ^ XORR; -> this is also correct but will give overflow
        int rightMost = XORR & -XORR;
        // Now divide all the elements into 2 buckets.
        // bucket 1 will contain elements with rightMost bit as set
        // bucket 2 will contain elements with rightMost bit as unset
        // in the end bucket 1 will contain 1 number and bucket 2 will contain 2nd number
        int b1 = 0, b2 = 0;
        for(int i = 0; i < n; i++){
            if(nums[i] & rightMost) b1 ^= nums[i]; // ^ to eliminate duplicate number
            else b2 ^= nums[i];
        }
        return vector<int>({b1, b2});
    }
};

TC - O(N), SC - O(1)