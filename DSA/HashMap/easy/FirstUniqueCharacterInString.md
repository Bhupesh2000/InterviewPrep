/*
Assignment 10 Q5
https://leetcode.com/problems/first-unique-character-in-a-string/description/

Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.

Example 1:
Input: s = "leetcode"
Output: 0
Explanation:
The character 'l' at index 0 is the first character that does not occur at any other index.

Example 2:
Input: s = "loveleetcode"
Output: 2

Example 3:
Input: s = "aabb"
Output: -1

Constraints:
1 <= s.length <= 10^5
s consists of only lowercase English letters.
*/

class Solution {
public:
    int firstUniqChar(string s) {
        vector<int> indexes(26, -1);
        for(int i = 0; i < s.size(); i++){
            int ind = s[i] - 'a';
            if(indexes[ind] >= 0) indexes[ind] = -2;
            else if(indexes[ind] == -1) indexes[ind] = i;
        }
        int ans = INT_MAX;
        for(int i = 0; i < 26; i++){
            if(indexes[i] >= 0) ans = min(indexes[i], ans);
        }
        return (ans == INT_MAX) ? -1 : ans;
    }
};

Approach 1 - using brute force, check for each element if it is duplicate or not and if not return the first non - duplicate
TC - O(N^2), SC - O(1)
Approach 2 - use 2 hash set, one which only contain non-duplicates and one which will contain all the chars that are present. Then get the non-duplicate with least index
TC - O(N), SC - O(N)
Approach 3 - use a hashmap that will store char and its index. If duplicate found then mark its index as -1
TC - O(N), SC - O(N).
Approach 4 - use a vector of size 26 and rest is same as approach 3
TC - O(N), SC - O(1)