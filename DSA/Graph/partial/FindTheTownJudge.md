/*
Assignment 11 Q4
https://leetcode.com/problems/find-the-town-judge

In a town, there are n people labeled from 1 to n. There is a rumor that one of these people is secretly the town judge.
If the town judge exists, then:
The town judge trusts nobody.
Everybody (except for the town judge) trusts the town judge.
There is exactly one person that satisfies properties 1 and 2.
You are given an array trust where trust[i] = [ai, bi] representing that the person labeled ai trusts the person labeled bi. If a trust relationship does not exist in trust array, then such a trust relationship does not exist.
Return the label of the town judge if the town judge exists and can be identified, or return -1 otherwise.

Example 1:
Input: n = 2, trust = [[1,2]]
Output: 2

Example 2:
Input: n = 3, trust = [[1,3],[2,3]]
Output: 3

Example 3:
Input: n = 3, trust = [[1,3],[2,3],[3,1]]
Output: -1
 
Constraints:
1 <= n <= 1000
0 <= trust.length <= 10^4
trust[i].length == 2
All the pairs of trust are unique.
ai != bi
1 <= ai, bi <= n
*/

Apprach 1-
class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<vector<int>> grid(n + 1, vector<int>(n + 1, -1));
        for(int i = 0; i < trust.size(); i++){
            int x = trust[i][0], y = trust[i][1];
            grid[x][0] = 0;
            grid[x][y] = 1;
        }
        int res = -1;
        for(int i = 1; i <= n; i++){
            if(grid[i][0] == -1){
                if(res == -1) res = i;
                else return -1;
            }
        }
        if(res == -1) return -1;
        for(int i = 1; i <= n; i++){
            if(i == res) continue;
            if(grid[i][res] != 1) return -1;
        }
        return res;
    }
};
TC - O(2n + trust.size()), SC - O(n^2)

--------------------------------------------------------------------------------------------------------------------------------------------

class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int >ind(n+1, 0);
        vector<int >out(n+1, 0);
        for(int i=0;i<trust.size();i++)
        {
            int a= trust[i][0];
            int b= trust[i][1];

            ind[b]++;
            out[a]++;
            
        }
        for(int i=1;i<=n;i++)
        {
            if(ind[i]==n-1 && out[i]==0)
            {
                return i;
            }
        }
        return -1;
    }
};

TC - O(n + trust.size()), SC - O(2*n)