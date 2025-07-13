/*
Assignment 7 Q14
https://leetcode.com/problems/find-duplicate-subtrees/

Given the root of a binary tree, return all duplicate subtrees.
For each kind of duplicate subtrees, you only need to return the root node of any one of them.
Two trees are duplicate if they have the same structure with the same node values.

Example 1:
Input: root = [1,2,3,4,null,2,4,null,null,4]
Output: [[2,4],[4]]

Example 2:
Input: root = [2,1,1]
Output: [[1]]

Example 3:
Input: root = [2,2,2,3,null,3,null]
Output: [[2,3],[3]] 

Constraints:
The number of the nodes in the tree will be in the range [1, 5000]
-200 <= Node.val <= 200
*/

Approach 1 - Brute force
For every node, generate a deep copy of its subtree and compare it with every other subtree using deep comparison.
Time complexity is very high and only useful as a teaching tool.

TC - O(N^3), SC - O(N).

📦 Brute Force Time Complexity Analysis (Find Duplicate Subtrees)

Let:
- N = number of nodes in the binary tree
- S = average size of the serialized string of a subtree

🔹 Step-by-Step Breakdown:

1. Traverse all N nodes → O(N)

2. For each node, serialize the entire subtree rooted at that node:
   - In the worst case (skewed tree), the size of a serialized string can be O(N)
   - Total serialization cost across all nodes: O(N) × O(N) = O(N²)

3. Insert each serialized string into a hash map:
   - Inserting and comparing each string takes O(S), where S can be O(N)
   - Total map operations: O(N × S) = O(N²)

✅ Final Time and Space Complexity:

- Time: O(N²)
- Space: O(N²) (to store all serialized strings in the map)

📌 Conclusion:
The brute force approach has quadratic time complexity due to repeated subtree serialization and expensive string operations, which is why it performs poorly on large trees.

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - Optimal Solution (Serialization + Hashing)
Use post-order traversal to serialize each subtree into a string.
Store each serialized form in a map<string, int> to count how many times each subtree appears.
The first time a subtree appears twice, store its root in the result.

class Solution {
    unordered_map<string, int> mp;
    vector<TreeNode*> res;

    string dfs(TreeNode* root){
        if(!root) return "#";

        string left = dfs(root -> left);
        string right = dfs(root -> right);

        string serial = to_string(root -> val) + "," + left + "," + right;
        mp[serial] ++;

        if(mp[serial] == 2) res.push_back(root);

        return serial;
    }

public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        dfs(root);
        return res;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 3 - Instead of serializing trees as long strings, assign a unique ID to every unique subtree structure. This reduces string overhead.
class Solution {
    unordered_map<string, int> serialToId;
    unordered_map<int, int> count;
    vector<TreeNode*> res;

    int ind = 1;

    int dfs(TreeNode* root){
        if(!root) return 0;

        int left = dfs(root -> left);
        int right = dfs(root -> right);

        string serial = to_string(root -> val) + "," + to_string(left) + "," + to_string(right);

        if(serialToId.count(serial) == 0){
            serialToId[serial] = ind ++;
        }

        int currInd = serialToId[serial];
        count[currInd] ++;

        if(count[currInd] == 2) res.push_back(root);
        return currInd;

    }
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        dfs(root);
        return res;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------

🔁 Recap of the Two Approaches

1. String Serialization + Hashing:
string serial = to_string(root->val) + "," + left + "," + right;

Stores the entire serialized string of the subtree in a map.
Time and space grows with the size of the string for each subtree.


2. Structure ID + Hashing:
string serial = to_string(root->val) + "," + to_string(leftID) + "," + to_string(rightID);

Stores a much shorter string (val,leftID,rightID) instead of full subtree strings.
Then assigns a unique integer ID to each unique structure.
Further comparisons are done using integers (faster).


🔍 Key Differences
| Feature                       | String Serialization       | Structure ID Approach            |
| ----------------------------- | -------------------------- | -------------------------------- |
| **Serialized Size**           | O(size of subtree)         | O(1) for each node (just 3 ints) |
| **Map Key Type**              | Long strings               | Short strings → then ints        |
| **String Concatenation Cost** | High (many allocations)    | Minimal                          |
| **Comparison in Map**         | String comparison (slow)   | Integer comparison (fast)        |
| **Duplicate Detection Speed** | Slower                     | Faster                           |
| **Space Usage**               | High (stores long strings) | Lower (stores integer IDs)       |


🧠 Why Structure ID is Better
1. Efficiency in Large Trees
In the string version, if a large subtree appears multiple times, you serialize it again and again.
This leads to repeated string operations — which are expensive.
In the ID version, you use previously computed IDs, which are cheap to handle.

2. Avoids Redundant Work
Structure ID reuses work done on subtrees: once a subtree is hashed, you never reserialize it.

3. Less Memory Overhead
Instead of storing potentially thousands of characters per subtree (in deep trees), you store:
    One int ID per subtree.
    One string per unique subtree (to assign ID).

📈 Time & Space Complexity
| Approach             | Time Complexity                           | Space Complexity |
| -------------------- | ----------------------------------------- | ---------------- |
| String Serialization | O(N \* H) (H = height of subtree strings) | O(N \* H)        |
| Structure ID         | **O(N)** (amortized)                      | **O(N)**         |

O(N) is possible because each subtree is visited once, and we build only short keys like val,leftID,rightID.

✅ Conclusion
| Metric                | String Version              | Structure ID Version         |
| --------------------- | --------------------------- | ---------------------------- |
| Simpler               | ✅ Yes                       | ❌ Slightly more logic        |
| Faster on Large Trees | ❌ No                        | ✅ Yes                        |
| Less Memory Usage     | ❌ No                        | ✅ Yes                        |
| Recommended           | For small trees or learning | ✅ For real use & performance |


