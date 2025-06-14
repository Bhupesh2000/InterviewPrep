/* Assignment-2 Q1
https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.
If target is not found in the array, return [-1, -1].
You must write an algorithm with O(log n) runtime complexity.

Example 1:
Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]

Example 2:
Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]

Example 3:
Input: nums = [], target = 0
Output: [-1,-1]

Constraints:
0 <= nums.length <= 105
-109 <= nums[i] <= 109
nums is a non-decreasing array.
-109 <= target <= 109
*/

class Solution {
    int searchRangeHelper(vector<int>& nums, int start, int end, int target, bool first){
        if(start > end) return -1;
        int mid = start + (end - start) / 2;
        if(nums[mid] == target){
            if(first){
                if(mid == start || nums[mid - 1] != target) return mid;
                else return searchRangeHelper(nums, start, mid - 1, target, first);
            }
            else{
               if(mid == end || nums[mid + 1] != target) return mid;
                else return searchRangeHelper(nums, mid + 1, end, target, first); 
            }
        }
        else if(nums[mid] > target) return searchRangeHelper(nums, start, mid - 1, target, first);
        else return searchRangeHelper(nums, mid + 1, end, target, first);
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int first = searchRangeHelper(nums, 0, nums.size() - 1, target, true);
        int last = (first == -1) ? -1 : searchRangeHelper(nums, first, nums.size() - 1, target, false);
        vector<int> ans;
        ans.push_back(first);
        ans.push_back(last);
        return ans;
    }
};