/*
https://leetcode.com/problems/combination-sum/description/

Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.
The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

Example 1:
Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.
Example 2:
Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]
Example 3:
Input: candidates = [2], target = 1
Output: []
 
Constraints:
1 <= candidates.length <= 30
2 <= candidates[i] <= 40
All elements of candidates are distinct.
1 <= target <= 40
*/

class Solution {
    void combinationSum(int index, vector<int>& candidates, int target, vector<vector<int>>& ans, vector<int>& currentCombination){
        if(index >= candidates.size() || target < 0) return;
        if(target == 0){
            ans.push_back(currentCombination);
            return;
        }
        currentCombination.push_back(candidates[index]);
        combinationSum(index, candidates, target - candidates[index], ans, currentCombination);
        currentCombination.pop_back();
        combinationSum(index + 1, candidates, target, ans, currentCombination);
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> currentCombination;
        combinationSum(0, candidates, target, ans, currentCombination);
        return ans;
    }
};

TC - O(2^target * k) 2^target for lets say arr[i] = 1 and target = 10. each pick and not pick will have 10 combinations, k is the no. of combinations(for pushing currentCombination into ans)
SC - k * x(x is for recursion stack)