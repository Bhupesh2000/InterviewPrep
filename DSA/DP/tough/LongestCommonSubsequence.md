/*
https://leetcode.com/problems/longest-common-subsequence/

Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.
A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
For example, "ace" is a subsequence of "abcde".
A common subsequence of two strings is a subsequence that is common to both strings.

Example 1:
Input: text1 = "abcde", text2 = "ace" 
Output: 3  
Explanation: The longest common subsequence is "ace" and its length is 3.
Example 2:
Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.
Example 3:
Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.
 
Constraints:
1 <= text1.length, text2.length <= 1000
text1 and text2 consist of only lowercase English characters.
*/

Approach 1 - Recursion
class Solution {
    int longestCommonSubsequence(string text1, string text2, int ind1, int ind2){
        if(ind1 < 0 || ind2 < 0) return 0;
        if(text1[ind1] == text2[ind2]) return 1 + longestCommonSubsequence(text1, text2, ind1 - 1, ind2 - 1);
        return max(longestCommonSubsequence(text1, text2, ind1 - 1, ind2), longestCommonSubsequence(text1, text2, ind1, ind2 - 1));
    }
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n1 = text1.size(), n2 = text2.size();
        return longestCommonSubsequence(text1, text2, n1 - 1, n2 - 1);
    }
};
TC - O(2^m * 2^n), SC - O(m + n)

Approach 2 - Memoization(indexes have been shifted to n1 + 1 and n2 + 1)
class Solution {
    int longestCommonSubsequence(string text1, string text2, int ind1, int ind2, vector<vector<int>>& dp){
        if(ind1 == 0 || ind2 == 0) return 0;
        if(dp[ind1][ind2] != -1) return dp[ind1][ind2];
        if(text1[ind1 - 1] == text2[ind2 - 1]) return dp[ind1][ind2] = 1 + longestCommonSubsequence(text1, text2, ind1 - 1, ind2 - 1, dp);
        return dp[ind1][ind2] = max(longestCommonSubsequence(text1, text2, ind1 - 1, ind2, dp), longestCommonSubsequence(text1, text2, ind1, ind2 - 1, dp));
    }
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n1 = text1.size(), n2 = text2.size();
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, -1));
        return longestCommonSubsequence(text1, text2, n1, n2, dp);
    }
};
TC - O(m * n), SC - O(m * n) + O(m + n)

Approach 3 - Recursion
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n1 = text1.size(), n2 = text2.size();
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1));
        for(int i = 0; i <= n1; i++) dp[i][0] = 0;
        for(int i = 0; i <= n2; i++) dp[0][i] = 0;
        for(int i = 1; i <= n1; i++){
            for(int j = 1; j <= n2; j++){
                if(text1[i - 1] == text2[j - 1]) dp[i][j] = 1 + dp[i - 1][j - 1];
                else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[n1][n2];
    }
};
TC - O(m * n), SC - O(m * n)