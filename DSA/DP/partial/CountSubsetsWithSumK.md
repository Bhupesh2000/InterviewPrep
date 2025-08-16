/*
https://www.naukri.com/code360/problems/count-subsets-with-sum-k_3952532?leftPanelTabValue=PROBLEM

You are given an array 'arr' of size 'n' containing positive integers and a target sum 'k'.
Find the number of ways of selecting the elements from the array such that the sum of chosen elements is equal to the target 'k'.
Since the number of ways can be very large, print it modulo 10 ^ 9 + 7.
Example:
Input: 'arr' = [1, 1, 4, 5]
Output: 3
Explanation: The possible ways are:
[1, 4]
[1, 4]
[5]
Hence the output will be 3. Please note that both 1 present in 'arr' are treated differently.
Detailed explanation ( Input/output format, Notes, Images )
Sample Input 1 :
4 5
1 4 4 5
Sample Output 1 :
 3
Explanation For Sample Output 1:
The possible ways are:
[1, 4]
[1, 4]
[5]
Hence the output will be 3. Please note that both 1 present in 'arr' are treated differently.
Sample Input 2 :
3 2
1 1 1
Sample Output 2 :
3
Explanation For Sample Output 1:
There are three 1 present in the array. Answer is the number of ways to choose any two of them.
Sample Input 3 :
3 40
2 34 5
Sample Output 3 :
0
Expected time complexity :
The expected time complexity is O('n' * 'k').
Constraints:
1 <= 'n' <= 100
0 <= 'arr[i]' <= 1000
1 <= 'k' <= 1000
*/

Approach 1 - Recursion -> O(2^n), O(n)

Approach 2 - Memoization ->
int Mod = pow(10, 9) + 7;
int findWays(vector<int>& arr, int k, int n, int ind, vector<vector<int>>& dp){
	if (ind == 0) {
        if (k == 0 && arr[0] == 0) return 2; // {} and {0}
        if (k == 0 || k == arr[0]) return 1;
        return 0;
    }
	if(dp[ind][k] != -1) return dp[ind][k];
	int notPick = findWays(arr, k, n, ind - 1, dp) % Mod;
	int pick = 0;
	if(k >= arr[ind]) pick = findWays(arr, k - arr[ind], n, ind - 1, dp) % Mod;
	return dp[ind][k] = (pick % Mod + notPick % Mod) % Mod;
}
int findWays(vector<int>& arr, int k)
{
	int n = arr.size();
	vector<vector<int>> dp(n, vector<int>(k + 1, -1));
	return findWays(arr, k, n, n - 1, dp);
}
TC - O(n * k), SC - O(n * k + n)

Approach 3 - dp
int findWays(vector<int>& arr, int k)
{
	int n = arr.size();
	vector<vector<int>> dp(n, vector<int>(k + 1, 0));
	for(int i = 0; i < n; i++) dp[i][0] = 1;
	if(arr[0] == 0) dp[0][0] = 2;
	else if(arr[0] <= k) dp[0][arr[0]] = 1;
	for(int i = 1; i < n; i++){
		for(int j = 1; j <= k; j++){
			int notPick = dp[i - 1][j];
			int pick = 0;
			if(j >= arr[i]) pick = dp[i - 1][j - arr[i]];
			dp[i][j] = (pick % Mod + notPick % Mod) % Mod;
		}
	}
	return dp[n - 1][k];
}
TC - O(n * k), SC - O(n * k)