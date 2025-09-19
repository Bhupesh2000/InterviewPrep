/*
https://leetcode.com/problems/permutations/description/

Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

Example 1:
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
Example 2:
Input: nums = [0,1]
Output: [[0,1],[1,0]]
Example 3:
Input: nums = [1]
Output: [[1]]
 
Constraints:
1 <= nums.length <= 6
-10 <= nums[i] <= 10
All the integers of nums are unique.
*/

Approach 1 - 
class Solution {
    void permute(vector<int>& nums, vector<vector<int>>& ans, vector<int>& currPermute, vector<int>& freq){
        if(currPermute.size() == nums.size()){
            ans.push_back(currPermute);
            return;
        }
        for(int i = 0; i < nums.size(); i++){
            if(freq[i] == 0){
                currPermute.push_back(nums[i]);
                freq[i] = 1;
                permute(nums, ans, currPermute, freq);
                currPermute.pop_back();
                freq[i] = 0;
            }
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> currPermute;
        vector<int> freq(nums.size(), 0);
        permute(nums, ans, currPermute, freq);
        return ans;
    }
};
TC - O(n! * n) (n! for no. of permutes, n for 0 -> n - 1 traversal)
SC - O(n)(for currPermute) + O(n)(for auxilary space) + O(n)(for freq) + O(n · n!)(for ans)

--------------------------------------------------------------------------------------------------------------------------------------------

class Solution {
    void permute(int ind, vector<int>& nums, vector<int>& currPermute, vector<vector<int>>& ans){
        if(currPermute.size() == nums.size()) ans.push_back(currPermute);
        for(int i = ind; i < nums.size(); i++){
            swap(nums[i], nums[ind]);
            currPermute.push_back(nums[ind]);
            permute(ind + 1, nums, currPermute, ans);
            currPermute.pop_back();
            swap(nums[i], nums[ind]);
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> currPermute;
        permute(0, nums, currPermute, ans);
        return ans;
    }
};
TC - O(n! * n) (n! for no. of permutes, n for 0 -> n - 1 traversal)
SC - O(n)(for currPermute) + O(n)(for auxilary space) + O(n · n!)(for ans)