/*
Assignment 6 Q8
https://leetcode.com/problems/remove-duplicate-letters/description/

Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Example 1:
Input: s = "bcabc"
Output: "abc"

Example 2:
Input: s = "cbacdcbc"
Output: "acdb"
 
Constraints:
1 <= s.length <= 10^4
s consists of lowercase English letters.
*/

Brute force solution - make all the subsequences and return the one with all the characters and smallest lexographical

Optimised Soltion - Using stack, an extra vector to store the last index of the elemnt and an unordered_set
class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> occurence(26, -1);
        for(int i = 0; i < s.size(); i++){
            occurence[s[i] - 'a'] = i;
        }

        stack<char> st;
        unordered_set<char> set;
        for(int i = 0; i < s.size(); i++){
            if(set.count(s[i]) != 0) continue;
            if(st.empty() || (st.top() < s[i])){
                st.push(s[i]);
                set.insert(s[i]);
            }
            else{
                while(!st.empty() && st.top() > s[i] && occurence[st.top() - 'a'] > i){
                    set.erase(st.top());
                    st.pop();
                }
                set.insert(s[i]);
                st.push(s[i]);
            }
        }

        string ans = "";

        while(!st.empty()){
            ans = st.top() + ans;
            st.pop();
        }

        return ans;

    }
};

TC - O(N), SC - O(N)
