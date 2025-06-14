/*
Given two strings s and t, return true if t is an anagram of s, and false otherwise.

Example 1:
Input: s = "anagram", t = "nagaram"
Output: true

Example 2:
Input: s = "rat", t = "car"
Output: false

Constraints:
1 <= s.length, t.length <= 5 * 104
s and t consist of lowercase English letters.
*/

class Solution {
public:
    bool isAnagram(string s, string t) {
        int n = s.size(), m = t.size();
        if(n != m) return false;
        vector<int> arr(26, 0);
        for(int i = 0; i < n; i++){
            int index1 = s[i] - 'a';
            int index2 = t[i] - 'a';
            arr[index1] ++;
            arr[index2] --;
        }
        for(int i = 0; i < 26; i++){
            if(arr[i] != 0) return false;
        }
        return true;
    }
};