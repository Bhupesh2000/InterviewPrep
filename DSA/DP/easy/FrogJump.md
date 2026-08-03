/*
https://www.naukri.com/code360/problems/frog-jump_3621012

There is a frog on the '1st' step of an 'N' stairs long staircase. The frog wants to reach the 'Nth' stair. 'HEIGHT[i]' is the height of the '(i+1)th' stair.If Frog jumps from 'ith' to 'jth' stair, the energy lost in the jump is given by absolute value of ( HEIGHT[i-1] - HEIGHT[j-1] ). If the Frog is on 'ith' staircase, he can jump either to '(i+1)th' stair or to '(i+2)th' stair. Your task is to find the minimum total energy used by the frog to reach from '1st' stair to 'Nth' stair.

For Example
If the given ‘HEIGHT’ array is [10,20,30,10], the answer 20 as the frog can jump from 1st stair to 2nd stair (|20-10| = 10 energy lost) and then a jump from 2nd stair to last stair (|10-20| = 10 energy lost). So, the total energy lost is 20.
Detailed explanation ( Input/output format, Notes, Images )
Constraints:
1 <= T <= 10
1 <= N <= 100000.
1 <= HEIGHTS[i] <= 1000 .

Time limit: 1 sec
Sample Input 1:
2
4
10 20 30 10
3
10 50 10
Sample Output 1:
20
0
Explanation of sample input 1:
For the first test case,
The frog can jump from 1st stair to 2nd stair (|20-10| = 10 energy lost).
Then a jump from the 2nd stair to the last stair (|10-20| = 10 energy lost).
So, the total energy lost is 20 which is the minimum. 
Hence, the answer is 20.

For the second test case:
The frog can jump from 1st stair to 3rd stair (|10-10| = 0 energy lost).
So, the total energy lost is 0 which is the minimum. 
Hence, the answer is 0.
Sample Input 2:
2
8
7 4 4 2 6 6 3 4 
6
4 8 3 10 4 4 
Sample Output 2:
7
2
*/

Approach 1 - Recursion
#include <bits/stdc++.h> 
int frogJump(int n, vector<int> &heights)
{
    if(n == 1) return 0;
    if(n == 2) return abs(heights[1] - heights[0]);

    return min(frogJump(n - 1, heights) + abs(heights[n - 1] - heights[n - 2]), frogJump(n - 2, heights) + abs(heights[n - 1] - heights[n - 3]));
}
TC - O(2^n), SC - O(n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - Memoization
#include <bits/stdc++.h> 
int frogJump(int n, vector<int> &heights, vector<int> &dp){
    if(n == 1) return 0;
    if(n == 2) return abs(heights[1] - heights[0]);
    if(dp[n] != -1) return dp[n];
    return dp[n] = min(frogJump(n - 1, heights, dp) + abs(heights[n - 1] - heights[n - 2]), frogJump(n - 2, heights, dp) + abs(heights[n - 1] - heights[n - 3]));
}
int frogJump(int n, vector<int> &heights)
{
    vector<int> dp(n + 1, -1);
    return frogJump(n, heights, dp);
}
Tc - O(n), SC - O(2n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 3 - Tabulation
int frogJump(int n, vector<int> &heights)
{
    if(n == 1) return 0;
    if(n == 2) return abs(heights[1] - heights[0]);
    vector<int> dp(n + 1);
    dp[1] = 0;
    dp[2] = abs(heights[1] - heights[0]);
    for(int i = 3; i <= n; i++){
        dp[i] = min(dp[i - 1] + abs(heights[i - 1] - heights[i - 2]), dp[i - 2] + abs(heights[i - 1] - heights[i - 3]));
    }
    return dp[n];
}
Tc - O(n), SC - O(n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 4 - dp with space optimisation
int frogJump(int n, vector<int> &heights)
{
    if(n == 1) return 0;
    if(n == 2) return abs(heights[1] - heights[0]);
    vector<int> dp(n + 1);
    int prev2 = 0, prev1 = abs(heights[1] - heights[0]);
    int curr;
    for(int i = 3; i <= n; i++){
        curr = min(prev1 + abs(heights[i - 1] - heights[i - 2]), prev2 + abs(heights[i - 1] - heights[i - 3]));
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}
Tc - O(n), SC - O(1)