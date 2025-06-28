/*
Assignment 5 Q16
https://www.geeksforgeeks.org/problems/longest-k-unique-characters-substring0853/1

Given a string s, you need to print the size of the longest possible substring with exactly k unique characters. If no possible substring exists, print -1.

Examples:
Input: s = "aabacbebebe", k = 3
Output: 7
Explanation: "cbebebe" is the longest substring with 3 distinct characters.

Input: s = "aaaa", k = 2
Output: -1
Explanation: There's no substring with 2 distinct characters.

Input: s = "aabaaab", k = 2
Output: 7
Explanation: "aabaaab" is the longest substring with 2 distinct characters.

Constraints:
1 ≤ s.size() ≤ 105
1 ≤ k ≤ 26
All characters are lowercase letters
*/

// User function template for C++

class Solution {
  public:
    int longestKSubstr(string &s, int k) {
        // your code here
        int n = s.size();
        if(k > n) return -1;
        unordered_set<char> unique;
        vector<int> freq(26, 0);
        int left = 0, right = 0;
        int maxLength = -1;
        while(right < n){
            freq[s[right] - 'a'] ++;
            if(unique.count(s[right]) == 0) unique.insert(s[right]);
            if(unique.size() == k){
                maxLength = max(maxLength, right - left + 1);
            }
            else if(unique.size() > k){
                freq[s[left] - 'a'] --;
                if(freq[s[left] - 'a'] == 0) unique.erase(s[left]);
                left ++;
            }
            right ++;
        }
        return maxLength;
    }
};

TC - O(2N), SC - O(N) + O(26)

Can be further optimised by moving from unique set to count variable
// User function template for C++

class Solution {
  public:
    int longestKSubstr(string &s, int k) {
        // your code here
        int n = s.size();
        if(k > n) return -1;
        vector<int> freq(26, 0);
        int left = 0, right = 0;
        int maxLength = -1;
        int count = 0;
        while(right < n){
            freq[s[right] - 'a'] ++;
            if(freq[s[right] - 'a'] == 1) count ++;
            if(count == k){
                maxLength = max(maxLength, right - left + 1);
            }
            else if(count > k){
                freq[s[left] - 'a'] --;
                if(freq[s[left] - 'a'] == 0) count --;
                left ++;
            }
            right ++;
        }
        return maxLength;
    }
};