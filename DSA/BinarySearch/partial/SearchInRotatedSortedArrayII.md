/*
Assignment 2 Q3
https://leetcode.com/problems/search-in-rotated-sorted-array-ii/description/

There is an integer array nums sorted in non-decreasing order (not necessarily with distinct values).
Before being passed to your function, nums is rotated at an unknown pivot index k (0 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,4,4,5,6,6,7] might be rotated at pivot index 5 and become [4,5,6,6,7,0,1,2,4,4].
Given the array nums after the rotation and an integer target, return true if target is in nums, or false if it is not in nums.
You must decrease the overall operation steps as much as possible.

Example 1:
Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true

Example 2:
Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false

Constraints:
1 <= nums.length <= 5000
-10^4 <= nums[i] <= 10^4
nums is guaranteed to be rotated at some pivot.
-10^4 <= target <= 10^4

Follow up: This problem is similar to Search in Rotated Sorted Array, but nums may contain duplicates. Would this affect the runtime complexity? How and why?
*/

class Solution {
    int findMinIndex(vector<int>& nums, int start, int end){
        while(start < end){
            while(start < end && nums[start] == nums[end]) start ++;
            int mid = start + (end - start) / 2;
            if(nums[mid] > nums[end]) start = mid + 1;
            else end = mid;
        }
        return start;
    }
    bool search(vector<int>& nums, int start, int end, int target){
        if(start > end) return false;
        int mid = start + (end - start) / 2;
        if(nums[mid] == target) return true;
        else if(nums[mid] > target) return search(nums, start, mid - 1, target);
        else return search(nums, mid + 1, end, target);
    }
public:
    bool search(vector<int>& nums, int target) {
        int minIndex = findMinIndex(nums, 0, nums.size() - 1);
        if(target >= nums[minIndex] && target <= nums[nums.size() - 1]) return search(nums, minIndex, nums.size() - 1, target);
        else return search(nums, 0, minIndex - 1, target);
    }
};