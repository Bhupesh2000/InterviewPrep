/*
https://leetcode.com/problems/combination-sum-ii/description/

Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.
Each number in candidates may only be used once in the combination.
Note: The solution set must not contain duplicate combinations.

Example 1:
Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: 
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]
Example 2:
Input: candidates = [2,5,2,1,2], target = 5
Output: 
[
[1,2,2],
[5]
]
 
Constraints:
1 <= candidates.length <= 100
1 <= candidates[i] <= 50
1 <= target <= 30
*/

class Solution {
    void combinationSum2(int index, vector<int>& candidates, int target, vector<vector<int>>& ans, vector<int>& currentCombination){
        if(target == 0){
            ans.push_back(currentCombination);
            return;
        }
        if(index >= candidates.size() || target < 0) return;
        currentCombination.push_back(candidates[index]);
        combinationSum2(index + 1, candidates, target - candidates[index], ans, currentCombination);
        currentCombination.pop_back();
        while(index < candidates.size() - 1 && candidates[index] == candidates[index + 1]) index++;
        combinationSum2(index + 1, candidates, target, ans, currentCombination);
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> currentCombination;
        sort(candidates.begin(), candidates.end());
        combinationSum2(0, candidates, target, ans, currentCombination);
        return ans;
    }
};

Time Complexity

Explore/search cost (backtracking, with dedup + pruning): O(2^n) in the worst case.
Sorting upfront: O(n log n).
Writing outputs (copying each found combination): O(∑|combination|) = O(k·L),
where k = number of valid combinations and L = average length of a combination.
Final TC: O(2^n + n log n + k·L).

Space Complexity
Call stack + current path: at most pick each element once ⇒ depth ≤ n ⇒ O(n) auxiliary.
Output storage: O(∑|combination|) = O(k·L).
Final SC:
Auxiliary: O(n)
Including results: O(n + k·L)