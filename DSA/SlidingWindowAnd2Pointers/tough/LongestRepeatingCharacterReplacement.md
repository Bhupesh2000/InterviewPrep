/*
Assignment 5 Q10
https://leetcode.com/problems/longest-repeating-character-replacement/

You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.
Return the length of the longest substring containing the same letter you can get after performing the above operations.

Example 1:
Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.

Example 2:
Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
There may exists other ways to achieve this answer too.
 
Constraints:
1 <= s.length <= 10^5
s consists of only uppercase English letters.
0 <= k <= s.length
*/

Recursive method will give O(N^2) tc and O(1) sc

Opitmised method
class Solution {
    int findMaxFreq(vector<int>& freq){
        int maximum = 0;
        for(int i = 0; i < 26; i++)
            maximum = max(maximum, freq[i]);
        return maximum;
    }
public:
    int characterReplacement(string s, int k) {
        vector<int> freq(26, 0);
        int left = 0, right = 0;
        int n = s.size();
        int maxLength = 0, maxFreq = 0;
        while(right < n){
            freq[s[right] - 'A'] ++;
            maxFreq = max(maxFreq, freq[s[right] - 'A']);
            while((right - left + 1) - maxFreq > k){
                freq[s[left] - 'A'] --;
                maxFreq = findMaxFreq(freq);
                left ++;
            }
            maxLength = max(maxLength, right - left + 1);
            right ++;
        }
        return maxLength;
    }
};

TC - O(2N * 26), SC - O(26)

We can leave this calculating maxFreq everytime in the inner loop, because we don't need to decrease the maxFreq.
MaxLength = maxFreq + k; so if we have found a maxLength, there is no point in looking for maxLength - 1.
We should rather look for only where we can increase maxFreq so that MaxLength can be increased.

class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> freq(26, 0);
        int left = 0, right = 0;
        int n = s.size();
        int maxLength = 0, maxFreq = 0;
        while(right < n){
            freq[s[right] - 'A'] ++;
            maxFreq = max(maxFreq, freq[s[right] - 'A']);
            while((right - left + 1) - maxFreq > k){
                freq[s[left] - 'A'] --;
                left ++;
            }
            maxLength = max(maxLength, right - left + 1);
            right ++;
        }
        return maxLength;
    }
};

TC - O(2N), SC - O(26)

We can also leave the decreasing the size of window when (right - left + 1) - maxFreq > k.
Because if lets say we have a window of size T, that means my ans is altlease T. So there is no point in decreasing the size of window less than T.

class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> freq(26, 0);
        int left = 0, right = 0;
        int n = s.size();
        int maxLength = 0, maxFreq = 0;
        while(right < n){
            freq[s[right] - 'A'] ++;
            maxFreq = max(maxFreq, freq[s[right] - 'A']);
            if((right - left + 1) - maxFreq > k){
                freq[s[left] - 'A'] --;
                left ++;
            }
            maxLength = max(maxLength, right - left + 1);
            right ++;
        }
        return maxLength;
    }
};

TC - O(N), SC - O(26)