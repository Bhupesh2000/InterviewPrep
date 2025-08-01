/*
https://leetcode.com/problems/single-number-ii/description/

Given an integer array nums where every element appears three times except for one, which appears exactly once. Find the single element and return it.
You must implement a solution with a linear runtime complexity and use only constant extra space.

Example 1:
Input: nums = [2,2,3,2]
Output: 3

Example 2:
Input: nums = [0,1,0,1,0,1,99]
Output: 99
 
Constraints:
1 <= nums.length <= 3 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
Each element in nums appears exactly three times except for one element which appears once.
*/

Approach 1 - Brute force check for all the numbers if it is appearing more than 1.
TC - O(N^2), SC - O(1)

Approach 2 - Use a hashmap
TC - O(N) + O(N / 3), SC - O(N / 3)

Approach 3 - counting the number of set bits on each position. No. of set bits for positions 0 to 31(since integers), will be a multiple of 3 except for the positions where the bit is set for element that is present only once.
Eg -
5 -> 1 0 1
5 -> 1 0 1
5 -> 1 0 1
6 -> 1 1 0
4 -> 1 0 0
4 -> 1 0 0
4 -> 1 0 0
-----------
sum  7 1 3

now only 1st and 2nd bit are not multiple of 3 so keep them as set bits else every bit as unset -> 1 1 0 = 6

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        for(int bitIndex = 0; bitIndex <= 31; bitIndex++){
            int cnt = 0;
            for(int j = 0; j < n; j++){ // check for each number if ith is set or not
                if(nums[j] & (1 << bitIndex)){ // check if ith bit is set or not
                    cnt++;
                }
            }
            if(cnt % 3 == 1){
                ans = ans | (1 << bitIndex); // setting ith bit as set
            }
        }
        return ans;
    }
};
TC - O(32 * N), SC - O(1)

Approach 4 - sort the array and then check which element is not repeating
TC - O(NlogN) + O(N), SC - (1)

Approach 5 - sort the array, start the counter from i = 1 and rather than traversing one by one, increase the counter by 3.
If at any pt., nums[i] != nums[i - 1], that means nums[i - 1] is the ans. Handle for edge case where the single element is present at the last
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int i = 1, n = nums.size();
        while(i < n){
            if(nums[i] != nums[i - 1]) return nums[i - 1];
            i += 3;
        }
        return nums[n - 1];
    }
};
TC - O(NlogN) + O(N / 3), SC - O(1)
** Approch 5 and 4 will be faster than 3.
NlogN will be less than N * 32. for log N = 32, N = 2^32, which won't be the case.

Approach 6 - concepts of bucket
Have 3 buckets, ones, twos and threes(the no. of times an element is seen)
* nums[i] will go into ones, if it is not in twos(no need to check for threes and the max time a number is repeated is 3)
* nums[i] will go into twos, if it is in ones
* nums[i] will go into threes, if it is in twos

** no need to store in threes, because it is not required.
There will be following operations - 
If not is twos, add in ones
If in ones, delete from ones and add in twos
If in twos, delete from twos

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int n = nums.size();
        int ones = 0, twos = 0;
        for(int i = 0; i < n; i++){
            ones = ((nums[i] ^ ones) & ~twos);
            twos = ((nums[i] ^ twos) & ~ones);
        }
        return ones;
    }
};
