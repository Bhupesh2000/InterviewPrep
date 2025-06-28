/*
Assignment 5 Q5
https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/description/

There are several cards arranged in a row, and each card has an associated number of points. The points are given in the integer array cardPoints.
In one step, you can take one card from the beginning or from the end of the row. You have to take exactly k cards.
Your score is the sum of the points of the cards you have taken.
Given the integer array cardPoints and the integer k, return the maximum score you can obtain.

Example 1:
Input: cardPoints = [1,2,3,4,5,6,1], k = 3
Output: 12
Explanation: After the first step, your score will always be 1. However, choosing the rightmost card first will maximize your total score. The optimal strategy is to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.

Example 2:
Input: cardPoints = [2,2,2], k = 2
Output: 4
Explanation: Regardless of which two cards you take, your score will always be 4.

Example 3:
Input: cardPoints = [9,7,7,9,7,7,9], k = 7
Output: 55
Explanation: You have to take all the cards. Your score is the sum of points of all cards.
 
Constraints:
1 <= cardPoints.length <= 105
1 <= cardPoints[i] <= 104
1 <= k <= cardPoints.length

*/

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int left = 0;
        int totalSum = 0;
        while(left < k){
            totalSum += cardPoints[left];
            left ++;
        }
        left --;
        int maxSum = totalSum;
        int right = cardPoints.size() - 1;
        if(k == right + 1) return maxSum;
        while(left >= 0){
            totalSum = totalSum + (cardPoints[right] - cardPoints[left]);
            maxSum = max(maxSum, totalSum);
            left --;
            right --;
        }
        return maxSum;
    }
};

TC - O(N), SC - O(1)

Recursive solution - 
TC - O(2^n), SC - O(N) -> recursive stack
int helper(vector<int>& cardPoints, int l, int h, int k){
    if (k==0)
        return 0;
    return max(cardPoints[l]+helper(cardPoints, l+1, h, k-1), cardPoints[h]+helper(cardPoints, l, h-1, k-1));
}

DP solution
TC - O(N), SC - O(N) -> store left and right sums for each i in 2 vectors