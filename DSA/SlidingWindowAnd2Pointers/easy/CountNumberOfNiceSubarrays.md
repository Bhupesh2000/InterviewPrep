/*
Assignment 5 Q7
https://leetcode.com/problems/count-number-of-nice-subarrays/

Given an array of integers nums and an integer k. A continuous subarray is called nice if there are k odd numbers on it.
Return the number of nice sub-arrays.

Example 1:
Input: nums = [1,1,2,1,1], k = 3
Output: 2
Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].

Example 2:
Input: nums = [2,4,6], k = 1
Output: 0
Explanation: There are no odd numbers in the array.

Example 3:
Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
Output: 16
 
Constraints:
1 <= nums.length <= 50000
1 <= nums[i] <= 10^5
1 <= k <= nums.length
*/

class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int left = -1, right = 0 ;
        int ans = 0, oddCount = 0;
        int n = nums.size();
        while(right < n){
            int sI = -1, eI = -1;
            for(int i = left + 1; i < right; i++){
                if(nums[i] % 2 != 0){
                    sI = i;
                    break;
                }
            }
            while(right < n && oddCount < k){
                if(nums[right] % 2 != 0){
                    if(sI == -1) sI = right;
                    oddCount ++;
                    if(oddCount == k) eI = right;
                }
                right ++;
                if(oddCount == k){
                    while(right < n && (nums[right] % 2 == 0)) right ++;
                    ans += ((right - eI) * (sI - left));
                    left = sI;
                    oddCount --;
                    break;
                }
            }
        }
        return ans;
    }
};

TC - O(N), SC - O(1)

recursive approach
start from i = 0 and find all substrings starting from i with k oddNumbers
TC - O(N^2), SC - O(1)