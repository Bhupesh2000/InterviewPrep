/*
Assignment 6 Q5
https://leetcode.com/problems/largest-rectangle-in-histogram/

Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

Example 1:
Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.

Example 2:
Input: heights = [2,4]
Output: 4
 
Constraints:
1 <= heights.length <= 10^5
0 <= heights[i] <= 10^4

*/

Brute Force Solution - 
get all index at which the height is lower than current height from both left and right of the current index.
area - current height * (rightIndex - leftIndex + 1).

TC = O(N^2), SC - O(1).

--------------------------------------------------------------------------------------------------------------------------------------------

Using two stacks
The same thing rather than using loop can be done via using 2 stacks and storing previous smaller number index and next smaller number index in two separate vectors. Then area  = (height[i] * (right[i] - left[i] + 1)).

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        stack<pair<int, int>> right;
        stack<pair<int, int>> left;

        vector<int> rightIndexes(n);
        vector<int> leftIndexes(n);

        for(int i = n - 1; i >= 0; i--){
            if(right.empty() || right.top().first < heights[i]){
                rightIndexes[i] = i;
            }
            else{
                int prevRight = i;
                while(!right.empty() && right.top().first >= heights[i]){
                    prevRight = max(prevRight, max(right.top().second, rightIndexes[right.top().second]));
                    right.pop();
                }
                rightIndexes[i] = prevRight;
            }
            right.push({heights[i], i});
        }

        for(int i = 0; i < n; i++){
            if(left.empty() || left.top().first < heights[i]){
                leftIndexes[i] = i;
            }
            else{
                int prevLeft = i;
                while(!left.empty() && left.top().first >= heights[i]){
                    prevLeft = min(prevLeft, min(left.top().second, leftIndexes[left.top().second]));
                    left.pop();
                }
                leftIndexes[i] = prevLeft;
            }
            left.push({heights[i], i});
        }

        int maxArea = 0;
        for(int i = 0; i < n; i++){
            maxArea = max(maxArea, (rightIndexes[i] - leftIndexes[i] + 1) * heights[i]);
        }

        return maxArea;
    }
};

In the above solution
TC - O(2N) -> next smaller index number(removal from stack + traversal on array) + O(2N) -> prev smaller index + O(N) -> area calc = O(5N).
SC - O(2N) -> two stacks + O(2N) -> two vectors = O(4N).

--------------------------------------------------------------------------------------------------------------------------------------------

The above solution can be done in both TC - O(2N) -> traversal + poping from stack and SC - O(N).

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        int maxArea = 0;
        for(int i = 0; i < heights.size(); i++){
            if(st.empty()) st.push(i);
            else{
                while(!st.empty() && heights[st.top()] > heights[i]){
                    int topElementI = st.top();
                    st.pop();
                    int nextsmallerI = i;
                    int prevsmallerI = -1;
                    if(!st.empty()) prevsmallerI = st.top();
                    maxArea = max(maxArea, heights[topElementI] * (nextsmallerI - prevsmallerI - 1));
                }
                st.push(i);
            }
        }

        while(!st.empty()){
            int topElementI = st.top();
            st.pop();
            int nextsmallerI = heights.size();
            int prevsmallerI = -1;
            if(!st.empty()) prevsmallerI = st.top();
            maxArea = max(maxArea, heights[topElementI] * (nextsmallerI - prevsmallerI - 1));
        }

        return maxArea;
    }
};