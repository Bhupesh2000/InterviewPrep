/*
Given a string consisting of lowercase characters and an integer k, the task is to count all possible substrings (not necessarily distinct) that have exactly k distinct characters. 

Examples :
Input: s = "abc", k = 2
Output: 2
Explanation: Possible substrings are ["ab", "bc"]

Input: s = "aba", k = 2
Output: 3
Explanation: Possible substrings are ["ab", "ba", "aba"]

Input: s = "aa", k = 1
Output: 3
Explanation: Possible substrings are ["a", "a", "aa"]

Constraints:
1 ≤ s.size() ≤ 106
1 ≤ k ≤ 26
*/

With sc - O(K), tc - O(N) [for all types of unicode chars]

// Helper function to count the number of substrings with at most k distinct characters
int countAtMostK(const string& s, int k) {
    int left = 0, right = 0, count = 0;
    unordered_map<char, int> freq;

    // Expand the window by moving 'right'
    while (right < s.size()) {
        freq[s[right]]++;  // Add current character to the frequency map

        // Shrink the window from the left if we exceed k distinct characters
        while (freq.size() > k) {
            freq[s[left]]--;         // Reduce count of char at 'left'
            if (freq[s[left]] == 0)  // If count becomes zero, remove from map
                freq.erase(s[left]);
            left++;                  // Move left pointer forward
        }

        // For each valid window, all substrings ending at 'right' and starting
        // from 'left' to 'right' are valid => (right - left + 1) substrings
        count += (right - left + 1);
        right++;
    }

    return count;
}

// Main function to count substrings with exactly k distinct characters
int substrCountWithKDistinct(const string& s, int k) {
    // Edge case: if k is 0, return 0
    if (k == 0) return 0;

    // Substrings with exactly k distinct characters =
    //    (substrings with at most k distinct) - (substrings with at most k-1 distinct)
    return countAtMostK(s, k) - countAtMostK(s, k - 1);
}

--------------------------------------------------------------------------------------------------------------------------------------------

With sc - O(1), tc - O(N) [for only lowercase letter(a - z)]
// Helper to count substrings with at most K distinct characters using array
int countAtMostK(const string& s, int k) {
    int left = 0, right = 0, count = 0, distinct = 0;
    int freq[26] = {0};  // Only lowercase letters

    while (right < s.size()) {
        // Add new character
        if (freq[s[right] - 'a'] == 0)
            distinct++;
        freq[s[right] - 'a']++;

        // Shrink window if too many distinct characters
        while (distinct > k) {
            freq[s[left] - 'a']--;
            if (freq[s[left] - 'a'] == 0)
                distinct--;
            left++;
        }

        // Count substrings ending at right
        count += (right - left + 1);
        right++;
    }

    return count;
}

// Main function to count substrings with exactly K distinct characters
int substrCountWithKDistinct(const string& s, int k) {
    if (k == 0) return 0;
    return countAtMostK(s, k) - countAtMostK(s, k - 1);
}
