/*
https://www.naukri.com/code360/problems/minimum-number-of-deletions-and-insertions_4244510?leftPanelTabValue=SUBMISSION

You are given 2 non-empty strings 's1' and 's2' consisting of lowercase English alphabets only.
In one operation you can do either of the following on 's1':
(1) Remove a character from any position in 's1'.
(2) Add a character to any position in 's1'.
Find the minimum number of operations required to convert string 's1' into 's2'.

Example:
Input: 's1' = "abcd", 's2' = "anc"
Output: 3
Explanation:
Here, 's1' = "abcd", 's2' = "anc".
In one operation remove 's1[3]', after this operation 's1' becomes "abc".    
In the second operation remove 's1[1]', after this operation 's1' becomes "ac".
In the third operation add 'n' in 's1[1]', after this operation 's1' becomes "anc".
Hence, the minimum operations required will be 3. It can be shown that there's no way to convert s1 into s2 in less than 3 moves.
Detailed explanation ( Input/output format, Notes, Images )
Sample Input 1 :
aaa
aa
Expected Answer :
1
Output on console :
1
Explanation For Sample Output 1:
For this test case,
's1' = "aaa", 's2' = "aa"
In one operation remove 's1[2]', after this operation 's1' becomes "aa".
Hence, the output will be 1.
Sample Input 2 :
edl 
xcqja
Expected Answer :
8
Output on console :
8
Expected Time Complexity :
Try to do this in O(n*m), where n is the length of string 's1' and 'm' is the length of string 's2'.
Constraints:
1 <= s1.length, s2.length <= 100
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

int canYouMake(string &s1, string &s2){
    int lcs = longestCommonSubsequence(s1, s2);
    int deletions = s1.size() - lcs;
    int insertions = s2.size() - lcs;

    return deletions + insertions;
}