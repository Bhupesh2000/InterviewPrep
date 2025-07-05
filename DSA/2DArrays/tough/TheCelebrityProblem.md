/*
Assignment 6 Q10
https://practice.geeksforgeeks.org/problems/the-celebrity-problem/1/?track=amazon-stacks&batchId=192

A celebrity is a person who is known to all but does not know anyone at a party. A party is being organized by some people. A square matrix mat[][] (n*n) is used to represent people at the party such that if an element of row i and column j is set to 1 it means ith person knows jth person. You need to return the index of the celebrity in the party, if the celebrity does not exist, return -1.

Note: Follow 0-based indexing.
Examples:
Input: mat[][] = [[1, 1, 0], [0, 1, 0], [0, 1, 1]]
Output: 1
Explanation: 0th and 2nd person both know 1st person. Therefore, 1 is the celebrity person. 

Input: mat[][] = [[1, 1], [1, 1]]
Output: -1
Explanation: Since both the people at the party know each other. Hence none of them is a celebrity person.

Input: mat[][] = [[1]]
Output: 0

Constraints:
1 <= mat.size()<= 1000
0 <= mat[i][j]<= 1
mat[i][i] == 1

*/

Approach 1 - Traversing to each and every element and checking how many elements does it know and how many elements know it.

class Solution {
  public:
    int celebrity(vector<vector<int> >& mat) {
        // code here
        int n = mat.size();
        vector<int> knowMe(n, 0);
        vector<int> IKnow(n, 0);
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i == j || mat[i][j] == 0) continue;
                knowMe[j] ++;
                IKnow[i] ++;
            }
        }
        
        for(int i = 0; i < n; i ++){
            if(IKnow[i] == 0){
                if(knowMe[i] == n - 1) return i;
                break;
            }
        }
        return -1;
    }
};

TC - O(N * N), SC - O(2N)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - 
Max number of celebrity is 1 and min number is 0.
So have 2 pointers(top and bottom), 1 at the 0th index and 2nd at n - 1th index. check for both top and bottom who cannot be a celebrity.
when top and bottom index meet, check for it doesnot know anyone and every one knows it.

class Solution {
  public:
    int celebrity(vector<vector<int> >& mat) {
        // code here
        int n = mat.size();
        int top = 0, bottom = n - 1;
        // checks who cannot be a celebrity
        while(top < bottom){
            if(mat[top][bottom] == 0) bottom --;
            else if(mat[bottom][top] == 0) top ++;
            else top ++;
        }
        // confirm for top index if it is a celebrity
        for(int i = 0; i < n; i++){
            if(top == i) continue;
            if(mat[top][i] == 1 || mat[i][top] == 0) return -1;
        }
        return top;
    }
};

TC - O(N), SC - O(1)