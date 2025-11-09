/*
https://www.naukri.com/code360/problems/minimum-insertions-to-make-a-string-palindrome_985293?leftPanelTabValue=PROBLEM

A palindrome string is one that reads the same backward as well as forward.
You are given a string 'str'.
Find the minimum number of characters needed to insert in 'str' to make it a palindromic string.
Example :
Input: 'str' = "abca"
Output: 1
Explanation:
If we insert the character ‘b’ after ‘c’, we get the string "abcba", which is a palindromic string. Please note that there are also other ways possible.
Detailed explanation ( Input/output format, Notes, Images )
Sample Input 1:
abca
Sample Output 1:
1
Explanation for input 1:
If we insert the character ‘b’ after ‘c’, we get the string "abcba", which is a palindromic string. Please note that there are also other ways possible.
Sample Input 2:
abcdefg
Sample Output 2:
6
Sample Input 3:
aaaaa
Sample Output 3:
0
Expected time complexity :
The expected time complexity is O(|str| ^ 2).
Constraints:
1 <= |str| <= 1000
Where |str| represents the length of the string 'str'.
*/

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

int longestPalindromeSubsequence(string& s)
{
    string s1 = s;
    string s2 = s;
    reverse(s2.begin(), s2.end());
    return longestCommonSubsequence(s1, s2);
}

int minimumInsertions(string &str)
{
	// MinimumInsertion = total length - longest palindrome subsequence
	int totalLength = str.size();
	return totalLength - longestPalindromeSubsequence(str);
}
