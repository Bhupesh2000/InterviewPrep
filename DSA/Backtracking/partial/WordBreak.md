/*
Assignment 4 Q15
https://leetcode.com/problems/word-break/description/

Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.
Note that the same word in the dictionary may be reused multiple times in the segmentation.

Example 1:
Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".
Example 2:
Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.
Example 3:
Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false
 
Constraints:
1 <= s.length <= 300
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 20
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique.
*/

class Solution {
    bool wordBreak(string s, int idx, unordered_set<string>& dict, vector<int>& dp){
        if(idx == s.size()) return true;
        if(dp[idx] != -1) return (dp[idx] == 0) ? false : true;
        for(int i = idx; i < s.size(); i++){
            if(dict.find(s.substr(idx, i - idx + 1)) != dict.end()){
                if(wordBreak(s, i + 1, dict, dp)){
                    dp[idx] = 1;
                    return true;
                }
            }
        }
        dp[idx] = 0;
        return false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict;
        vector<int> dp(s.size(), -1);
        for(string str : wordDict) dict.insert(str);
        return wordBreak(s, 0, dict, dp);
    }
};