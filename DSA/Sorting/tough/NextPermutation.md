/*
Assignment 2 Q19
https://leetcode.com/problems/next-permutation/

A permutation of an array of integers is an arrangement of its members into a sequence or linear order.
For example, for arr = [1,2,3], the following are all the permutations of arr: [1,2,3], [1,3,2], [2, 1, 3], [2, 3, 1], [3,1,2], [3,2,1].
The next permutation of an array of integers is the next lexicographically greater permutation of its integer. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).
For example, the next permutation of arr = [1,2,3] is [1,3,2].
Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not have a lexicographical larger rearrangement.
Given an array of integers nums, find the next permutation of nums.
The replacement must be in place and use only constant extra memory.

Example 1:
Input: nums = [1,2,3]
Output: [1,3,2]
Example 2:
Input: nums = [3,2,1]
Output: [1,2,3]
Example 3:
Input: nums = [1,1,5]
Output: [1,5,1]
 
Constraints:
1 <= nums.length <= 100
0 <= nums[i] <= 100
*/

Approach 1 - Brute Force
Step 1 - Create all the permutations -> O(N! * N)
Step2 - Linear search / (sort and then binary search)
Step 3 - Find the next permute

Approach 2 -
Step 1 - Traverse from back and find first decreasing seq(because for increasing every combination will be less than current)
Step 2 - find the next bigger element than the first decreasing element and swap
Step 3 - Sort the rest

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return;
        int idx = n - 1;
        while(idx > 0){
            if(nums[idx] > nums[idx - 1]) break;
            idx --;
        }
        idx --;
        int idx2 = idx + 1;
        if(idx != -1){
            for(int i = idx + 1; i < n; i++){
                if(nums[i] > nums[idx] && nums[i] < nums[idx2]) idx2 = i;
            }
            swap(nums[idx], nums[idx2]);
        }
        sort(nums.begin() + idx + 1, nums.end());
    }
};

TC - O(N) + O(N) + O(NlogN), SC - O(1)
