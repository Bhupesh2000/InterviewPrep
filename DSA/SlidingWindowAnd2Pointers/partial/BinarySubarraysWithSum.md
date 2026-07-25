/*
Assignment - 5  Q9
https://leetcode.com/problems/binary-subarrays-with-sum/description/

Given a binary array nums and an integer goal, return the number of non-empty subarrays with a sum goal.
A subarray is a contiguous part of the array.

Example 1:
Input: nums = [1,0,1,0,1], goal = 2
Output: 4
Explanation: The 4 subarrays are bolded and underlined below:
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]

Example 2:
Input: nums = [0,0,0,0,0], goal = 0
Output: 15
 
Constraints:
1 <= nums.length <= 3 * 104
nums[i] is either 0 or 1.
0 <= goal <= nums.length

*/

Understand this approach correctly -> very much usable
If at ith index total sum is x.
and there exist an index till which sum is x - k, then there exist a subarray
So keep a count of all the indexes where sum x - k exists

This approach is usable in a variety of question.

class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int k) {
        int prefixSum = 0, ans = 0;
        unordered_map<int, int> sumCount;
        sumCount[0] = 1;
        for(int i = 0; i < nums.size(); i++){
            prefixSum += nums[i];
            int prefix = prefixSum - k;
            if(sumCount.count(prefix) != 0)
                ans += sumCount[prefix];
            sumCount[prefixSum] ++;
        }
        return ans;
    }
};

TC - O(N), SC - O(N) for hashmap


This approach works like solve(<= sum) - solve(<= sum - 1)
class Solution {
    int numSubarraysLessThanEqualSum(vector<int>& nums, int k){
        if(k < 0) return 0;
        int count = 0, left = 0, right = 0;
        int n = nums.size();
        int currSum = 0;
        while(right < n){
            currSum += nums[right];
            while(left < n && currSum > k){
                currSum = currSum - nums[left];
                left ++;
            }
            count += (right - left + 1);
            right ++;
        }
        return count;
    }
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return numSubarraysLessThanEqualSum(nums, goal) - numSubarraysLessThanEqualSum(nums, goal - 1);
    }
};

TC - O(N), SC - O(1)


This approach works like CountNumberOfNiceSubarrays -> since nums is binary,
the 1s play the role of "odd numbers" there. A subarray with sum == goal is
a subarray with exactly `goal` ones in it. Collect the positions of the 1s
(with -1 and n as sentinels), then for every window of `goal` consecutive
ones, multiply the number of zeros available on the left (gap to previous
one) by the number of zeros available on the right (gap to next one).
goal == 0 needs to be handled separately - count all-zero runs using the
C(len+1, 2) trick.

class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int n = nums.size();

        if (goal == 0) {
            int ans = 0, zeros = 0;
            for (int x : nums) {
                if (x == 0) zeros++;
                else zeros = 0;
                ans += zeros;
            }
            return ans;
        }

        vector<int> ones;
        ones.push_back(-1);
        for (int i = 0; i < n; i++)
            if (nums[i] == 1) ones.push_back(i);
        ones.push_back(n);

        int m = ones.size() - 2;
        int ans = 0;
        for (int i = 1; i + goal - 1 <= m; i++) {
            int left = ones[i] - ones[i - 1];
            int right = ones[i + goal] - ones[i + goal - 1];
            ans += left * right;
        }
        return ans;
    }
};

TC - O(N), SC - O(N) for storing the positions of 1s
