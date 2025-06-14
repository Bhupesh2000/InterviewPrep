/*
Given two strings s and t, determine if they are isomorphic.
Two strings s and t are isomorphic if the characters in s can be replaced to get t.
All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.

Example 1:
Input: s = "egg", t = "add"
Output: true
Explanation:
The strings s and t can be made identical by:
Mapping 'e' to 'a'.
Mapping 'g' to 'd'.

Example 2:
Input: s = "foo", t = "bar"
Output: false
Explanation:
The strings s and t can not be made identical as 'o' needs to be mapped to both 'a' and 'r'.

Example 3:
Input: s = "paper", t = "title"
Output: true

Constraints:
1 <= s.length <= 5 * 104
t.length == s.length
s and t consist of any valid ascii character.
*/

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int n = s.size(), m = t.size();
        if(n != m) return false;
        unordered_map<char, char> mp1;
        unordered_map<char, char> mp2;
        for(int i = 0; i < n; i++){
            if(mp1.count(s[i]) == 0 && mp2.count(t[i]) == 0){
                mp1[s[i]] = t[i];
                mp2[t[i]] = s[i];
            }
            else if(mp1.count(s[i]) == 0) return false;
            else if(mp2.count(t[i]) == 0) return false;
            else{
                if(mp1[s[i]] != t[i] || mp2[t[i]] != s[i]) return false;
            }
        }
        return true;
    }
};