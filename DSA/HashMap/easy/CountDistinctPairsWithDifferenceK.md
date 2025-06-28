/*
Assignment - 5 Q3
https://www.geeksforgeeks.org/problems/count-distinct-pairs-with-difference-k1233/1

Given an integer array of size n and a non-negative integer k, count all distinct pairs with a difference equal to k, i.e., A[i] - A[j] = k.

Example 1:
Input: array = {1, 5, 4, 1, 2}, k = 0
Output: 1
Explanation: There is only one pair (1, 1) whose difference equal to 0.

Example 2;
Input: array = {1, 5, 3}, k = 2
Output: 2
Explanation: There are two pairs (5, 3) and (1, 3) whose difference equal to 2.

Your Task:
You don't need to read or print anything. Your task is to complete the function TotalPairs() which takes array and k as input parameters and returns the count of all distinct pairs.

Expected Time Complexity: O(n)
Expected Space Complexity: O(n)

Constraints:
2 <= n <= 104
0 <= k <= 104
1 <= nums[i] <= 106

class Solution {
  public:
    int TotalPairs(vector<int> nums, int k) {
        // Code here
        int ans = 0;
        unordered_map<int, int> seen;
        for(int i = 0; i < nums.size(); i++){
            seen[nums[i]] ++;
        }
        for(int i = 0; i < nums.size(); i++){
            int diff = nums[i] - k;
            if(seen.count(diff) > 0){
                if(k == 0 && seen[diff] > 1){
                    ans ++;
                }
                else if(k != 0 && seen[diff] > 0){
                    ans ++;
                }
                seen[diff] = 0;
            }
        }
        return ans;
    }
};

TC - O(N), SC - O(N)

can be done via 2-pointers as well
TC - O(NlogN), SC - O(1) -> if no set use to keep track of duplicates, O(N) -> if set used to keep track of duplicates

brute force
TC = O(N^2), SC- O(N) -> to keep track of duplicates

brute force 2
TC = O(N^3), SC - O(1), for every possible ans, check if that pair has been considered or not