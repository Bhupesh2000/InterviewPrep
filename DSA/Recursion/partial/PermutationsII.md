/*
Assignment 4 Q12
https://leetcode.com/problems/permutations-ii/description/

Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.

Example 1:
Input: nums = [1,1,2]
Output:
[[1,1,2],
 [1,2,1],
 [2,1,1]]
Example 2:
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 
Constraints:
1 <= nums.length <= 8
-10 <= nums[i] <= 10
*/

class Solution {
    void permuteUnique(int index, vector<int>& current, vector<bool>& used, vector<int>& nums, vector<vector<int>>& ans){
        if(current.size() == nums.size()){
            ans.push_back(current);
            return;
        }

        for(int i = 0; i < nums.size(); i++){
            if(used[i]) continue;
            current.push_back(nums[i]);
            used[i] = true;
            permuteUnique(i + 1, current, used, nums, ans);
            current.pop_back();
            used[i] = false;
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> current;
        vector<bool> used(nums.size(), false);
        permuteUnique(0, current, used, nums, ans);
        return ans;
    }
};