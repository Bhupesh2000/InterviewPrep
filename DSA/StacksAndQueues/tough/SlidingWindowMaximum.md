/*
Assignment 6 Q13
https://www.geeksforgeeks.org/sum-minimum-maximum-elements-subarrays-size-k/

You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
Return the max sliding window.

Example 1:
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

Example 2:
Input: nums = [1], k = 1
Output: [1]

Constraints:

1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
1 <= k <= nums.length

*/

Solution 1 - using a nested loop, TC - O(N - k) * k, SC - O(N) for ans array

Solution 2 - using deque -> learn about it

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;
        vector<int> ans;
        for(int i = 0; i < k; i++){
            if(dq.empty() || nums[dq.back()] >= nums[i]) dq.push_back(i);
            else{
                while(!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
                dq.push_back(i);
            }
        }
        ans.push_back(nums[dq.front()]);
        int left = 0, right = k;
        while(right < nums.size()){
            if(dq.front() == left) dq.pop_front();
            left ++;
            if(dq.empty() || nums[dq.back()] >= nums[right]) dq.push_back(right);
            else{
                while(!dq.empty() && nums[dq.back()] <= nums[right]) dq.pop_back();
                dq.push_back(right);
            }
            right ++;
            ans.push_back(nums[dq.front()]);
        }
        return ans;

    }
};

TC - O(N), SC - O(N + k) - ans array + deque

Can also be done using an ordered_hashmap