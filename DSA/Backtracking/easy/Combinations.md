/* Assignment 3 Q8
https://leetcode.com/problems/combinations/description/

Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].
You may return the answer in any order.

Example 1:
Input: n = 4, k = 2
Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
Explanation: There are 4 choose 2 = 6 total combinations.
Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.

Example 2:
Input: n = 1, k = 1
Output: [[1]]
Explanation: There is 1 choose 1 = 1 total combination. 

Constraints:
1 <= n <= 20
1 <= k <= n
*/

class Solution {
    void combine(int index, int n, int k, vector<int> curr, vector<vector<int>>& ans){
        if(k == 0){
            ans.push_back(curr);
            return;
        }

        for(int i = index; i <= n; i ++){
            curr.push_back(i);
            combine(i + 1, n, k - 1, curr, ans);
            curr.pop_back();
        }
    }
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> curr;
        combine(1, n, k, curr, ans);
        return ans;
    }
};

SC -
| Component                 | Complexity       | Explanation                                                     |
| ------------------------- | ---------------- | --------------------------------------------------------------- |
| **Recursive stack**       | `O(K)`           | At most `k` recursive calls deep, since you choose `k` elements |
| **Current list (`curr`)** | `O(K)`           | Each recursive call maintains a list of at most `k` elements    |
| **Answer list (`ans`)**   | `O(K × C(n, k))` | You store `C(n, k)` combinations, each of size `k`              |

TC - 
| Component              | Complexity       | Explanation                                               |
| ---------------------- | ---------------- | --------------------------------------------------------- |
| Number of combinations | `C(n, k)`        | Total number of valid combinations generated              |
| Time per combination   | `O(k)`           | Each combination has `k` elements and is built one by one |
| Total time             | `O(k × C(n, k))` | Generating and copying each combination into the result   |
