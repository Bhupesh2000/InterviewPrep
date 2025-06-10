/*
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

Example 1:
Input: nums = [3,2,3]
Output: [3]
Example 2:

Input: nums = [1]
Output: [1]

Example 3:
Input: nums = [1,2]
Output: [1,2]

Constraints:
1 <= nums.length <= 5 * 104
-109 <= nums[i] <= 109
*/

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans;
        if(n <= 2){
            ans.push_back(nums[0]);
            if(n == 2 && nums[0] != nums[1]) ans.push_back(nums[1]);
            return ans;
        }
        int n1 = nums[0], n2, count1 = 0, count2 = 0;
        int i = 0;
        while(i < n && nums[i] == n1){
            count1 ++;
            i ++;
        }
        if(i == n){
            ans.push_back(n1);
            return ans;
        }
        n2 = nums[i];
        count2 = 0;
        while(i < n){
            if(nums[i] == n1) count1 ++;
            else if(nums[i] == n2) count2 ++;
            else if (count1 == 0) {
                n1 = nums[i];
                count1 = 1;
            } else if (count2 == 0) {
                n2 = nums[i];
                count2 = 1;
            } else {
                count1--;
                count2--;
            }
            i ++;
        }
        count1 = 0;
        count2 = 0;
        for(i = 0; i < n; i++){
            if(nums[i] == n1) count1 ++;
            if(nums[i] == n2) count2 ++;
        }
        if(count1 > (n / 3)) ans.push_back(n1);
        if(count2 > (n / 3) && n1 != n2) ans.push_back(n2);

        return ans;
    }
};