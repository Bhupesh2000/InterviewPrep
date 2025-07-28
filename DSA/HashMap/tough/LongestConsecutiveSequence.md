/*
Assignment 10 Q12
https://leetcode.com/problems/longest-consecutive-sequence/

Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.
You must write an algorithm that runs in O(n) time.
 
Example 1:
Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.

Example 2:
Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9

Example 3:
Input: nums = [1,0,1,2]
Output: 3

Constraints:
0 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
*/

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.size() <= 1) return nums.size();
        unordered_set<int> st(nums.begin(), nums.end());
        int ans = 1;
        for(int i : st){
            if(st.count(i - 1) == 0){
                int currCount = 0;
                while(st.count(i) > 0){
                    currCount ++;
                    i ++;
                }
                ans = max(ans, currCount);
            }
        }
        return ans;
    }
};

| Variant              | Time Complexity  |
| -------------------- | ---------------- |
| Pure brute force     | ❌ **O(n³)**      |
| Brute force with set | ✅ **O(n²)**      |
| Sort-based           | ✅ **O(n log n)** |
| Set-based optimal    | ✅ **O(n)**       |
