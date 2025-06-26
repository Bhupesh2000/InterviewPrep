/*
Assignment 5 Q15
https://leetcode.com/problems/minimum-window-substring/

Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".
The testcases will be generated such that the answer is unique.

Example 1:
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

Example 2:
Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.

Example 3:
Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.

Constraints:
m == s.length
n == t.length
1 <= m, n <= 105
s and t consist of uppercase and lowercase English letters.
*/

class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.size(), m = t.size();
        if(n < m) return "";
        vector<int> freq(52, 0);
        int count = 0;
        for(int i = 0; i < m; i++){
            int index = (t[i] >= 'A' && t[i] <= 'Z') ? t[i] - 'A' : t[i] - 'a' + 26;
            freq[index] ++;
            if(freq[index] == 1) count ++;
        }
        string ans = "";
        int left = 0, right = 0;
        while(right < n){
            int rightIndex = (s[right] >= 'A' && s[right] <= 'Z') ? s[right] - 'A' : s[right] - 'a' + 26;
            freq[rightIndex] --;
            if(freq[rightIndex] == 0) count --;
            int sI = -1;
            while(count == 0){
                int leftIndex = (s[left] >= 'A' && s[left] <= 'Z') ? s[left] - 'A' : s[left] - 'a' + 26;
                sI = left;
                freq[leftIndex] ++;
                if(freq[leftIndex] == 1) count ++;
                left ++;
            }
            if(sI != -1){
                if(ans == ""){
                    ans = s.substr(sI, right - sI + 1);
                }
                else if(ans.size() > (right - sI + 1)){
                    ans = s.substr(sI, right - sI + 1);
                }
            }
            right ++;
        }
        return ans;
    }
};

Keep in mind taking of sI. else Memory limit can exceed
Question can be upgraded to all kind of 256 characters

SC - O(2N) + O(M), TC - O(52)
