/*
https://leetcode.com/problems/palindrome-partitioning/description/

Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.

Example 1:
Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Example 2:
Input: s = "a"
Output: [["a"]]
 
Constraints:
1 <= s.length <= 16
s contains only lowercase English letters.
*/

class Solution {
    bool isPalindrome(string& s, int start, int end){
        while(start < end){
            if(s[start] != s[end]) return false;
            start ++;
            end --;
        }
        return true;
    }
    void partition(string& s, int idx, vector<string>& currPartitions, vector<vector<string>>& ans){
        if(idx == s.size()){
            ans.push_back(currPartitions);
            return;
        }
        for(int i = idx; i < s.size(); i++){
            if(isPalindrome(s, idx, i)){
                string str = s.substr(idx, i - idx + 1);
                currPartitions.push_back(str);
                partition(s, i + 1, currPartitions, ans);
                currPartitions.pop_back();
            }
        }
    }
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        vector<string> currPartitions;
        partition(s, 0, currPartitions, ans);
        return ans;
    }
};