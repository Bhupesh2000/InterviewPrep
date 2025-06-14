/* Assignment-2 Q2
https://leetcode.com/problems/search-insert-position/

Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
You must write an algorithm with O(log n) runtime complexity.

Example 1:
Input: nums = [1,3,5,6], target = 5
Output: 2

Example 2:
Input: nums = [1,3,5,6], target = 2
Output: 1

Example 3:
Input: nums = [1,3,5,6], target = 7
Output: 4
 
Constraints:
1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums contains distinct values sorted in ascending order.
-104 <= target <= 104

*/

class Solution {
    int searchInsert(vector<int>& nums, int start, int end, int target){
        if(start == end)
            return (nums[start] >= target) ? start : start + 1;

        int mid = start + (end - start) / 2;
        
        if(nums[mid] == target) return mid;
        else if(nums[mid] > target){
            if(mid == start || nums[mid - 1] < target) return mid;
            else return searchInsert(nums, start, mid - 1, target);
        }
        else{
            if(mid == end || nums[mid + 1] > target) return mid + 1;
            else return searchInsert(nums, mid + 1, end, target);
        }
    }
public:
    int searchInsert(vector<int>& nums, int target) {
        return searchInsert(nums, 0, nums.size() - 1, target);
    }
};