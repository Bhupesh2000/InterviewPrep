/*
Assignment 10 Q4
https://leetcode.com/problems/repeated-dna-sequences/description/

The DNA sequence is composed of a series of nucleotides abbreviated as 'A', 'C', 'G', and 'T'.
For example, "ACGAATTCCG" is a DNA sequence.
When studying DNA, it is useful to identify repeated sequences within the DNA.
Given a string s that represents a DNA sequence, return all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule. You may return the answer in any order.

Example 1:
Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
Output: ["AAAAACCCCC","CCCCCAAAAA"]

Example 2:
Input: s = "AAAAAAAAAAAAA"
Output: ["AAAAAAAAAA"]

Constraints:
1 <= s.length <= 10^5
s[i] is either 'A', 'C', 'G', or 'T'.
*/

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        if(s.size() <= 10) return {};
        string pattern = s.substr(0, 10);
        unordered_set<string> seen;
        unordered_set<string> ans;
        seen.insert(pattern);
        int i = 0, j = 10;
        while(j < s.size()){
            pattern.erase(0, 1); // will take tc O(10)
            // pattern += (s[j] - s[i]); -> not allowed in cpp
            // pattern -= s[i]; -> string - char is not allowed in cpp
            pattern += s[j];
            if(seen.count(pattern) > 0) ans.insert(pattern);
            seen.insert(pattern);
            i ++;
            j ++;
        }
        vector<string> res;
        for(string it : ans){
            res.push_back(it);
        }
        return res;
    }
};

* **TC:** `O(N)`
* **SC:** `O(3N)` → from `seen`, `ans`, and temporary `pattern` strings

Let’s look at other possible approaches and their trade-offs.

---

## ✅ 1. **Rolling Hash with Bitmasking (Optimized Space)**

### 🔍 Idea:

* Since the string only has 4 possible chars (`A`, `C`, `G`, `T`), encode each into **2 bits**
* A 10-letter DNA string → 20 bits total
* Use an `int` as a rolling hash key, avoiding full string storage

### 📉 Space Reduced:

* Instead of storing strings, you store only hash integers
* **SC:** `O(N)` (or even less if using fixed-size bitmask/hash table)

---

## ✅ 2. **Trie (Prefix Tree)**

### 🔍 Idea:

* Build a trie as you process each 10-letter substring
* Store only the necessary characters, with early pruning if repetition found

### 📉 Pros:

* Can reduce memory if many substrings share common prefixes

### 📈 Cons:

* Slightly higher constant factors
* More complex to implement and manage

---

## ✅ 3. **Fixed-size Hash Table (Since Possible Patterns Are Limited)**

### 🔍 Observation:

* 4 possible chars → `4^10 = 1,048,576` total possible sequences
* You can use a **fixed-size array of booleans or counters** to track which sequences have appeared

### 📉 Benefits:

* Constant-time lookup
* **SC:** `O(1)` — since max unique sequences is fixed

### 🚨 Trade-off:

* May still need a mapping function (e.g. rolling hash) to convert string → index

---

## ✅ 4. **Suffix Array (Overkill here, but theoretical option)**

### 🔍 Idea:

* Generate all suffixes of the string and sort them
* Check adjacent substrings for duplicates

### 📈 TC: `O(n log n)`

### 📉 SC: `O(n)`

### ⚠️ Not ideal for short patterns like 10, but worth knowing for general substring matching

---

## ✅ Summary Table:

| Approach               | TC         | SC    | Notes                          |
| ---------------------- | ---------- | ----- | ------------------------------ |
| Sliding window + set   | O(n)       | O(3n) | Simple, effective              |
| Rolling hash (bitmask) | O(n)       | O(n)  | Most space efficient           |
| Trie                   | O(n·k)     | O(n)  | Space can be lower in practice |
| Fixed-size array       | O(n)       | O(1)  | Constant memory, fast lookup   |
| Suffix array           | O(n log n) | O(n)  | Theoretical, overkill here     |

---
