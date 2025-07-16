/*
Assignment - 8 Q11
https://leetcode.com/problems/top-k-frequent-words/

Given an array of strings words and an integer k, return the k most frequent strings.
Return the answer sorted by the frequency from highest to lowest. Sort the words with the same frequency by their lexicographical order.

Example 1:
Input: words = ["i","love","leetcode","i","love","coding"], k = 2
Output: ["i","love"]
Explanation: "i" and "love" are the two most frequent words.
Note that "i" comes before "love" due to a lower alphabetical order.

Example 2:
Input: words = ["the","day","is","sunny","the","the","the","sunny","is","is"], k = 4
Output: ["the","is","sunny","day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words, with the number of occurrence being 4, 3, 2 and 1 respectively.
 
Constraints:
1 <= words.length <= 500
1 <= words[i].length <= 10
words[i] consists of lowercase English letters.
k is in the range [1, The number of unique words[i]]
 
Follow-up: Could you solve it in O(n log(k)) time and O(n) extra space?
*/

Approach 1 - Using brute force
Approach
Use an unordered map to count how many times each word appears.
For k iterations:
Find the word with the maximum frequency.
If multiple words have the same frequency, pick the one that comes first alphabetically.
Add this word to the result and remove it from the map.
Return the list of top k words.
This is a brute-force method and can be improved with a heap or full sort, but it's easy to understand.

Complexity
Time complexity:
O(n+k⋅m)
Where n is the number of total words, and m is the number of unique words.
In each of the k iterations, we may scan up to m words.

Space complexity:
O(m)
For storing the word frequencies in the hash map and result array.

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - using hashmap and heap

typedef pair<int, string> psi;

struct Compare{
    bool operator()(const psi& a, const psi& b){
        if(a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    }
};

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        int n = words.size();
        unordered_map<string, int> freq;
        for(int i = 0; i < n; i++){
            freq[words[i]] ++;
        }

        priority_queue<psi, vector<psi>, Compare> pq;

        for(auto it : freq){
            pq.push({it.second, it.first});
            if(pq.size() > k) pq.pop();
        }

        vector<string> ans(k);
        for(int i = k - 1; i >= 0; i--){
            ans[i] = pq.top().second;
            pq.pop();
        }

        return ans;
    }
};

TC - O(n + nlogk + k), SC - O(n + k)
