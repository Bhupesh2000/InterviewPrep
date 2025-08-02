/*
Assignment 10 Q18
https://leetcode.com/problems/palindrome-pairs/

You are given a 0-indexed array of unique strings words.
A palindrome pair is a pair of integers (i, j) such that:
0 <= i, j < words.length,
i != j, and
words[i] + words[j] (the concatenation of the two strings) is a palindrome.
Return an array of all the palindrome pairs of words.
You must write an algorithm with O(sum of words[i].length) runtime complexity.

Example 1:
Input: words = ["abcd","dcba","lls","s","sssll"]
Output: [[0,1],[1,0],[3,2],[2,4]]
Explanation: The palindromes are ["abcddcba","dcbaabcd","slls","llssssll"]

Example 2:
Input: words = ["bat","tab","cat"]
Output: [[0,1],[1,0]]
Explanation: The palindromes are ["battab","tabbat"]

Example 3:
Input: words = ["a",""]
Output: [[0,1],[1,0]]
Explanation: The palindromes are ["a","a"]
 
Constraints:
1 <= words.length <= 5000
0 <= words[i].length <= 300
words[i] consists of lowercase English letters.
*/

Approach 1 - Brute force
Pair each word with another and check if it is palindrome or not
✅ Time Complexity
Total Time = O(n² × L)
O(n²) for all pairs
O(L) per pair to check if it's a palindrome (assuming average word length L)

✅ Space Complexity
O(1) (ignoring the output) — only constant extra space used for string building and palindrome checking
If counting output: O(k) where k is the number of valid palindrome pairs

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - using hashmap
class Solution {
    bool checkPalindrome(string str){
        int i = 0, j = str.size() - 1;
        while(i < j){
            if(str[i] != str[j]) return false;
            i ++;
            j --;
        }
        return true;
    }
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        int n = words.size();
        vector<vector<int>> ans;
        unordered_map<string, int> index;
        for(int i = 0; i < n; i++){
            string temp = words[i];
            reverse(temp.begin(), temp.end());
            index[temp] = i;
        }
        // Edge case when words[i] = ""
        if(index.count("")){
            int ind = index[""];
            for(int i = 0; i < n; i++){
                if(i == ind) continue;
                if(checkPalindrome(words[i])) ans.push_back(vector<int>{i, ind}); // {ind, i} will be handled below
            }
        }

        for(int i = 0; i < n; i++){
            string left = "", right = "";
            for(int j = 0; j < words[i].length(); j++){
                left += words[i][j];
                right = words[i].substr(j + 1);
                if(index.count(left) && index[left] != i && checkPalindrome(right)){
                    ans.push_back({i, index[left]});
                }
                if(index.count(right) && index[right] != i && checkPalindrome(left)){
                    ans.push_back({index[right], i});
                }
            }
        }

        return ans;
    }
};

### ✅ **Time Complexity**
Let:
* `n` = number of words
* `L` = average length of a word

#### 1. **Reversing all words and inserting into map**
for(int i = 0; i < n; i++){
    string temp = words[i];
    reverse(temp.begin(), temp.end());
    index[temp] = i;
}
* Time: O(n \* L)

#### 2. **Handling empty string case**
if(index.count("")){
    for(int i = 0; i < n; i++){
        checkPalindrome(words[i]);  // O(L) per word
    }
}
* Worst-case Time: O(n \* L)

#### 3. **Main logic (for each word, split into left/right substrings)**
for(int i = 0; i < n; i++){
    for(int j = 0; j < words[i].length(); j++){
        left += words[i][j]; // O(1)
        right = words[i].substr(j + 1); // O(L - j)

        checkPalindrome(left) / checkPalindrome(right)  // O(L)
        index.count(left) or index.count(right) // O(1)
    }
}

* Outer loop: `O(n)`
* Inner loop (over characters): `O(L)`
* Substring + palindrome check: `O(L)` per iteration
  So overall this part is: `O(n * L^2)`
### 🧠 **Total Time Complexity:**
```
O(n * L^2)
```
This is acceptable for small `n` and `L`, but might TLE for upper bounds unless optimized further with tries or pruning.

### ✅ **Space Complexity**
* `unordered_map<string, int> index` → stores all reversed words
  → **O(n \* L)**
* `ans` stores all valid palindrome pairs → in worst-case could be `O(n²)`
  (if every word can form palindrome with every other word)
* Intermediate strings `left`, `right` → negligible (`O(L)` per iteration)
### 🧠 **Total Space Complexity:**
```
O(n * L + k)
```
Where `k` is the number of palindrome pairs found (output size).

### ✅ Summary

| Metric           | Complexity        |
| ---------------- | ----------------- |
| Time Complexity  | **O(n \* L²)**    |
| Space Complexity | **O(n \* L + k)** |
