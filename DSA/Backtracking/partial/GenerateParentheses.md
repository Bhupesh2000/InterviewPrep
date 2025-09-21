/*
Assignment 3 - Q7
https://leetcode.com/problems/generate-parentheses/description/
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

Example 1:
Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

Example 2:
Input: n = 1
Output: ["()"] 

Constraints:
1 <= n <= 8
*/

Recursive Approach using Stack
class Solution {
public:
    bool isValidParenthesis(string &s){
        stack<char>st;
        for(int i = 0; i<s.length();i++){
            if((!st.empty()) && (st.top() == '(' && s[i] == ')'))st.pop();
            else st.push(s[i]);
        }
        return st.empty();
    }

    void solve(int n,string &curr,vector<string>&result){
        if(curr.length() == 2*n){
            if(isValidParenthesis(curr)){
                result.push_back(curr); 
            }
            return;
        }

        curr.push_back('(');
        solve(n,curr,result);
        curr.pop_back();
        curr.push_back(')');
        solve(n,curr,result);
        curr.pop_back();
    }

    vector<string> generateParenthesis(int n) {
        vector<string>result;
        string currStr = "";
        solve(n,currStr,result);

        return result;
    }
};

Time complexity:
    Worst Case:O(2^(2n) * 2n)
Space complexity:
    stack space of recursion: O(2n) , i.e depth of the recursive tree
    stack used in isValidParenthesis: O(n)

--------------------------------------------------------------------------------------------------------------------------------------------

class Solution {
    void generateParenthesis(int left, int right, string current, int n, vector<string>& ans){
        if(current.size() == 2 * n){
            ans.push_back(current);
            return;
        }

        if(left < n) generateParenthesis(left + 1, right, current + "(", n, ans);
        if(right < left) generateParenthesis(left, right + 1, current + ")", n, ans);
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        generateParenthesis(0, 0, "", n, ans);
        return ans;
    }
};

Space complexity:
| Component                  | Complexity                                     |
| -------------------------- | ---------------------------------------------- |
| Recursive stack            | `O(N)`                                         |
| Result storage             | `O(N * Cn)`                                    |
| Current string (`current`) | `O(N)` per call — but amortized over recursion |
Cn is catalan number

Time complexity:
    O(N * Cn)

