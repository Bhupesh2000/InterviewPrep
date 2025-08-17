/*
Assignment 12 Q19
https://practice.geeksforgeeks.org/problems/longest-common-substring/0

You are given two strings s1 and s2. Your task is to find the length of the longest common substring among the given strings.

Examples:
Input: s1 = "ABCDGH", s2 = "ACDGHR"
Output: 4
Explanation: The longest common substring is "CDGH" with a length of 4.
Input: s1 = "abc", s2 = "acb"
Output: 1
Explanation: The longest common substrings are "a", "b", "c" all having length 1.
Input: s1 = "YZ", s2 = "yz"
Output: 0
Constraints:
1 <= s1.size(), s2.size() <= 10^3
Both strings may contain upper and lower case alphabets.
*/

class Solution {
  public:
    int longestCommonSubstr(string& s1, string& s2) {
       int n = s1.size(), m = s2.size();
       vector<vector<int>> dp(n + 1, vector<int>(m + 1));
       for(int i = 0; i <= n; i++) dp[i][0] = 0;
       for(int i = 0; i <= m; i++) dp[0][i] = 0;
       int maxLCS = 0;
       for(int i = 1; i <= n; i++){
           for(int j = 1; j <= m; j++){
               if(s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
               else dp[i][j] = 0;
               maxLCS = max(maxLCS, dp[i][j]);
           }
       }
       return maxLCS;
    }
};
