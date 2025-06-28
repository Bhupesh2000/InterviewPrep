/*
Assignment 5 Q11
https://leetcode.com/problems/max-consecutive-ones-iii/

Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the array if you can flip at most k 0's.

Example 1:
Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.

Example 2:
Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10
Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.

Constraints:
1 <= nums.length <= 10^5
nums[i] is either 0 or 1.
0 <= k <= nums.length

*/

Recursive approach
Make all subarray - Tc - O(N^2), Sc - O(1)

Optimised Approach
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size(), countZero = 0;
        int maxLength = 0;
        int left = 0, right = 0;
        while(right < n){
            if(nums[right] == 0) countZero ++;
            if(countZero <= k){
                maxLength = max(maxLength, right - left + 1);
            }
            else{
                if(nums[left] == 0) countZero --;
                left ++;
            }
            right ++;
        }
        return maxLength;
    }
};

TC - O(2N), SC - O(1).

an inner loop can also be used where if(countZero <= k) to while(countZero <= k), but that won't be required as we need the max length. So no point in shrinking the window size.
In that case TC - O(2N), SC - O(1).