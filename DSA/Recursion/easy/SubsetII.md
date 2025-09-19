/*
https://leetcode.com/problems/subsets-ii/description/

Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.

Example 1:
Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
Example 2:
Input: nums = [0]
Output: [[],[0]]
 
Constraints:
1 <= nums.length <= 10
-10 <= nums[i] <= 10
*/

class Solution {
    void subsetsWithDup(int ind, vector<int>& nums, vector<int>& currSubset, vector<vector<int>>& ans){
        ans.push_back(currSubset);
        for(int i = ind; i < nums.size(); i++){
            if(i > ind && nums[i] == nums[i - 1]) continue;
            currSubset.push_back(nums[i]);
            subsetsWithDup(i + 1, nums, currSubset, ans);
            currSubset.pop_back();
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        vector<int> currSubset;
        subsetsWithDup(0, nums, currSubset, ans);
        return ans;
    }
};