/*
https://www.naukri.com/code360/problems/longest-palindromic-subsequence_842787?leftPanelTabValue=PROBLEM

You have been given a string ‘A’ consisting of lower case English letters. Your task is to find the length of the longest palindromic subsequence in ‘A’.
A subsequence is a sequence generated from a string after deleting some or no characters of the string without changing the order of the remaining string characters. (i.e. “ace” is a subsequence of “abcde” while “aec” is not).
A string is said to be palindrome if the reverse of the string is the same as the actual string. For example, “abba” is a palindrome, but “abbc” is not a palindrome.
Detailed explanation ( Input/output format, Notes, Images )
Constraints:
1 <= T <= 10
1 <= N <= 10 ^ 2
Where ‘T’ is the number of test cases, and ‘N’ is the length of the string.
Sample Input 1:
2
bbabcbcab
bbbab
Sample Output 1:
7
4
Explanation of Sample Input 1:
For the first test case, the longest palindromic subsequence is “babcbab”, which has a length of 7. “bbbbb” and “bbcbb” are also palindromic subsequences of the given string, but not the longest one.
For the second test case, the longest palindromic subsequence is “bbbb”, which has a length of 4.
Sample Input 2:
3
cbbd
bebeeed
abcd
Sample Output 2:
2
4
1
*/

#include <bits/stdc++.h> 
int longestCommonSubsequence(string& text1, string& text2) {
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

int longestPalindromeSubsequence(string s)
{
    string s1 = s;
    string s2 = s;
    reverse(s2.begin(), s2.end());
    return longestCommonSubsequence(s1, s2);
}