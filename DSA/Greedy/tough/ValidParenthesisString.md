/*
https://leetcode.com/problems/valid-parenthesis-string/description/

Given a string s containing only three types of characters: '(', ')' and '*', return true if s is valid.
The following rules define a valid string:
Any left parenthesis '(' must have a corresponding right parenthesis ')'.
Any right parenthesis ')' must have a corresponding left parenthesis '('.
Left parenthesis '(' must go before the corresponding right parenthesis ')'.
'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string "".
 
Example 1:
Input: s = "()"
Output: true

Example 2:
Input: s = "(*)"
Output: true

Example 3:
Input: s = "(*))"
Output: true
 
Constraints:
1 <= s.length <= 100
s[i] is '(', ')' or '*'.
*/

if there are no *, we can keep a count variable
for each '(' cnt ++, ')' cnt --;
if(cnt < 0 at any pt) return false;
at end cnt == 0

Approach 1 - using recursion -> for each * checkout all 3 possibilities using cnt approach for each combination
TC - O(3^N), SC - O(N)

Approach 2 - using memoization, dp for index and count
TC - O(N^2), SC - O(N^2)

Approach 3 - rather than keeping cnt, keep a range of count(min and max). Won't do min < 0 because cnt -1 is not possible
class Solution {
public:
    bool checkValidString(string s) {
        int min = 0, max = 0;
        for(char c : s){
            if(c == '('){
                min ++;
                max ++;
            }
            else if(c == ')'){
                min --;
                max --;
            }
            else{
                min --;
                max ++;
            }
            if(min < 0) min = 0;
            if(max < 0) return false;
        }
        return min == 0;
    }
};

TC - O(N), SC - O(1)