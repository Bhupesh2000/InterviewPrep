/*
Assignment 10 Q15
https://leetcode.com/problems/subsets/

Given an integer array nums of unique elements, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.

Example 1:
Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:
Input: nums = [0]
Output: [[],[0]]
 
Constraints:
1 <= nums.length <= 10
-10 <= nums[i] <= 10
All the numbers of nums are unique.
*/

nums = [1 2 3]
        0 1 2

        No. of subsets - 2^n = 1 << n
        Traverse 0 to 2^(n - 1)
         2 1 0    0 -> No, 1 -> Yes
    0    0 0 0 -> []
    1    0 0 1 -> [3]
    2    0 1 0 -> [2]
    3    0 1 1 -> [2, 3]
    4    1 0 0 -> [1]
    5    1 0 1 -> [1, 3]
    6    1 1 0 -> [1, 2]
    7    1 1 1 -> [1, 2, 3]

Approach 1 - using recursion

Approach 2 - 
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> allSubsets;
        int n = nums.size();
        int noOfSubsets = 1 << n;
        for(int i = 0; i < noOfSubsets; i++){      // -> 2^n
            vector<int> subset;
            for(int j = 0; j < n; j++){            // -> n
                // check if jth bit of i is set or not
                if(i & (1 << j)) subset.push_back(nums[j]);
            }
            allSubsets.push_back(subset);
        }
        return allSubsets;
    }
};
TC - O(n * 2^n), SC - O(n * 2^N) -> 2^n(no. of subsets), n(size of 1 subset, not exactly n but equivalent to n)

