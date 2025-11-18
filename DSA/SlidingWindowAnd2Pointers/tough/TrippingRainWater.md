/*
https://leetcode.com/problems/trapping-rain-water/

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

Example 1:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
Example 2:
Input: height = [4,2,0,3,2,5]
Output: 9

Constraints:
n == height.length
1 <= n <= 2 * 10^4
0 <= height[i] <= 10^5
*/

total area will be sum of water on each building. water on each building will be minimum of max leftHeight till now and max rightHeight till now minus the height of the current building

Approach 1-
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> leftMax(n);
        vector<int> rightMax(n);
        leftMax[0] = height[0];
        rightMax[n - 1] = height[n - 1];
        for(int i = 1; i < n; i++){
            leftMax[i] = max(height[i], leftMax[i - 1]);
            rightMax[n - 1 - i] = max(height[n - 1 - i], rightMax[n - i]);
        }
        int total = 0;
        for(int i = 0; i < n; i++){
            if(min(leftMax[i], rightMax[i]) - height[i] > 0) total += (min(leftMax[i], rightMax[i]) - height[i]);
        }

        return total;
    }
};
TC - O(2N), SC - O(2N)

********************************************************************************************************************************************

Approach 2 -
In the above approach we are maintaining 2 different arrays for getting left and right max. This can be eliminated using 2 pointers and maintaing leftMax and rightMax height till now.
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int leftMax = height[0], rightMax = height[n - 1];
        int l = 0, r = n - 1;
        int total = 0;
        while(l < r){
            if(leftMax < height[l]) leftMax = height[l];
            if(rightMax < height[r]) rightMax = height[r];
            if(min(leftMax, rightMax) - height[l] > 0) total += min(leftMax, rightMax) - height[l];
            else if(min(leftMax, rightMax) - height[r] > 0) total += min(leftMax, rightMax) - height[r];
            if(height[l] > height[r]) r --;
            else l ++;
        }

        return total;
    }
};
TC- O(N), SC - O(1)