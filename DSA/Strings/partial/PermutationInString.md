/*
Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
In other words, return true if one of s1's permutations is the substring of s2.

Example 1:
Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").

Example 2:
Input: s1 = "ab", s2 = "eidboaoo"
Output: false

Constraints:
1 <= s1.length, s2.length <= 104
s1 and s2 consist of lowercase English letters.
*/

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        if(m < n) return false;

        unordered_map<char, int> mp;
        int count = 0;
        for(int i = 0; i < n; i++){
            if(mp.count(s1[i]) == 0){
                mp[s1[i]] = 1;
                count++;
            }
            else mp[s1[i]] ++;
        }

        for(int i = 0; i < n; i++){
            if(mp.count(s2[i]) != 0){
                mp[s2[i]] --;
                if(mp[s2[i]] == 0) count --;
                if(mp[s2[i]] == -1) count ++;
            }
        }

        if(count == 0) return true;

        int i = 0, j = n - 1;

        while(j + 1 < m){
            if(mp.count(s2[i]) != 0){
                mp[s2[i]] ++;
                if(mp[s2[i]] == 1) count ++;
                if(mp[s2[i]] == 0) count --;
            }
            i ++;
            j ++;
            if(mp.count(s2[j]) != 0){
                mp[s2[j]] --;
                if(mp[s2[j]] == 0) count --;
                if(mp[s2[j]] == -1) count ++;
                if(count == 0) return true;
            }
        }
        return false;
    }
};