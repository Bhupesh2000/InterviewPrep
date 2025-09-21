/*
Assignment-4 Q20
https://leetcode.com/problems/restore-ip-addresses/description/

A valid IP address consists of exactly four integers separated by single dots. Each integer is between 0 and 255 (inclusive) and cannot have leading zeros.
For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.
Given a string s containing only digits, return all possible valid IP addresses that can be formed by inserting dots into s. You are not allowed to reorder or remove any digits in s. You may return the valid IP addresses in any order.

Example 1:
Input: s = "25525511135"
Output: ["255.255.11.135","255.255.111.35"]
Example 2:
Input: s = "0000"
Output: ["0.0.0.0"]
Example 3:
Input: s = "101023"
Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
 
Constraints:
1 <= s.length <= 20
s consists of digits only.
*/

class Solution {
    // Helper recursive function
    // s       : input string
    // idx     : current index in s
    // cnt     : number of parts formed so far (max = 4)
    // n       : total length of s
    // cur     : current IP address string being built
    // ans     : vector to collect all valid IP addresses
    void restoreIpAddresses(string &s, int idx, int cnt, int n, string &cur, vector<string> &ans) {
        // Remaining characters in s
        int remChars = n - idx;
        // Remaining parts to be filled (we need exactly 4 total)
        int remParts = 4 - cnt;

        // Prune: not enough or too many characters left to complete 4 valid parts
        if (remChars < remParts || remChars > 3 * remParts) return;

        // Base case: if we already placed 4 parts
        if (cnt == 4) {
            // If we've consumed all characters, add to result
            if (idx == n) ans.push_back(cur);
            return;
        }

        // Try segment lengths = 1, 2, 3
        for (int len = 1; len <= 3 && idx + len <= n; ++len) {
            // Leading zero check: "0" is valid, but "00", "01", ... are not
            if (len > 1 && s[idx] == '0') break;

            // Convert substring to integer
            int val = stoi(s.substr(idx, len));
            if (val > 255) break; // IP part must be in [0, 255]

            // Save current length of cur string (for backtracking later)
            int before = cur.size();

            // Add a dot before appending if cur is not empty (not the first part)
            if (!cur.empty()) cur.push_back('.');

            // Append this segment to cur
            cur.append(s, idx, len);

            // Recurse to build the next part
            restoreIpAddresses(s, idx + len, cnt + 1, n, cur, ans);

            // Backtrack: erase the characters we just added (segment + optional dot)
            cur.resize(before);
        }
    }

public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> ans;       // stores all valid IP addresses
        string cur;               // current IP string being built
        restoreIpAddresses(s, 0, 0, s.size(), cur, ans);
        return ans;
    }
};
