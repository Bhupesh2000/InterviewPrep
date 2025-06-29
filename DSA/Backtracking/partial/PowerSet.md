/*
Assignment 3 Q10
https://www.geeksforgeeks.org/powet-set-lexicographic-order/
Explore the bitmasking and binary number approaches

Power Set P(S) of a set S is the set of all subsets of S. For example S = {a, b, c} then P(s) = {{}, {a}, {b}, {c}, {a,b}, {a, c}, {b, c}, {a, b, c}}. If S has n elements in it then P(s) will have 2n elements

Examples
Input: s = "ab"
Output: "", "a", "b", "ab"
Explanation: The power set of "ab" includes all possible subsets: empty set, single characters, and full string.

Input: s = "abc"
Output: "", "a", "b", "c", "ab", "bc", "ac", "abc"
Explanation: The power set of "abc" includes all subsets formed by choosing any combination of its characters.

Input: s = "a"
Output: "", "a"
Explanation: The power set of "a" consists of the empty set and the single character itself.
*/

Backtracking Approach

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void backtrack(int index, string& s, string& current, vector<string>& ans) {
    if (!current.empty()) ans.push_back(current);

    for (int i = index; i < s.size(); i++) {
        current.push_back(s[i]);               // choose character
        backtrack(i + 1, s, current, ans);     // explore
        current.pop_back();                    // undo choice
    }
}

vector<string> generateSubsetsBacktracking(string s) {
    sort(s.begin(), s.end());                  // ensure lexicographical order
    vector<string> ans;
    string current;
    backtrack(0, s, current, ans);
    return ans;
}

--------------------------------------------------------------------------------------------------------------------------------------------

Bitmasking Approach

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> generateSubsetsBitmask(string s) {
    sort(s.begin(), s.end());                  // ensure lexicographical order
    int n = s.length();
    vector<string> subsets;

    int total = 1 << n;                        // total subsets = 2^n
    for (int i = 1; i < total; i++) {          // skip empty subset if needed
        string subset = "";
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {                // check if j-th bit is set
                subset += s[j];
            }
        }
        subsets.push_back(subset);
    }

    sort(subsets.begin(), subsets.end());      // sort final results
    return subsets;
}

--------------------------------------------------------------------------------------------------------------------------------------------

Binary String Construction Approach

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> generateSubsetsBinary(string s) {
    sort(s.begin(), s.end());
    int n = s.length();
    vector<string> subsets;

    for (int i = 0; i < (1 << n); i++) {
        string binary = "";
        int num = i;

        // Convert number to binary representation (of length n)
        for (int j = 0; j < n; j++) {
            binary = char('0' + num % 2) + binary;
            num /= 2;
        }

        string subset = "";
        for (int j = 0; j < n; j++) {
            if (binary[j] == '1') {
                subset += s[j];
            }
        }

        if (!subset.empty()) subsets.push_back(subset);
    }

    sort(subsets.begin(), subsets.end());
    return subsets;
}

--------------------------------------------------------------------------------------------------------------------------------------------

| Method         | Time Complexity | Space Complexity | Notes                            |
| -------------- | --------------- | ---------------- | -------------------------------- |
| Backtracking   | O(2ⁿ × n)       | O(n × 2ⁿ)        | Clean recursion, avoids bit ops  |
| Bitmasking     | O(2ⁿ × n)       | O(n × 2ⁿ)        | Fast, no recursion               |
| Binary Strings | O(2ⁿ × n)       | O(n × 2ⁿ)        | Extra binary conversion overhead |

✅ Conclusion:
All three have same asymptotic complexities.

Bitmasking is often fastest in practice due to fewer allocations and simple logic.

Backtracking is clean and flexible, especially when constraints or pruning is involved.

Binary string method is a bit heavier due to manual binary string construction.
