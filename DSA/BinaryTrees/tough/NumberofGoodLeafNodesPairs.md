/*
Assignment7 Q9
https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/description/

You are given the root of a binary tree and an integer distance. A pair of two different leaf nodes of a binary tree is said to be good if the length of the shortest path between them is less than or equal to distance.

Return the number of good leaf node pairs in the tree.

 

Example 1:


Input: root = [1,2,3,null,4], distance = 3
Output: 1
Explanation: The leaf nodes of the tree are 3 and 4 and the length of the shortest path between them is 3. This is the only good pair.
Example 2:


Input: root = [1,2,3,4,5,6,7], distance = 3
Output: 2
Explanation: The good pairs are [4,5] and [6,7] with shortest path = 2. The pair [4,6] is not good because the length of ther shortest path between them is 4.
Example 3:

Input: root = [7,1,4,6,null,5,3,null,null,null,null,null,2], distance = 3
Output: 1
Explanation: The only good pair is [2,5].
 

Constraints:

The number of nodes in the tree is in the range [1, 2^10].
1 <= Node.val <= 100
1 <= distance <= 10

*/

Approach 1 ->
Traverse the tree and build an undirected adjacency list.
While doing that, collect all leaf nodes.
For every leaf:
Run BFS up to distance k.
Whenever you reach another leaf within distance k, increment the answer.
Since every pair gets counted twice (A → B and B → A), return ans / 2
int countPairs(TreeNode* root, int k) {
    unordered_map<TreeNode*, vector<TreeNode*>> graph;
    vector<TreeNode*> leaves;

    // Build graph + collect leaves
    function<void(TreeNode*, TreeNode*)> build =
        [&](TreeNode* node, TreeNode* parent) {
            if (!node) return;

            if (!node->left && !node->right)
                leaves.push_back(node);

            if (parent) {
                graph[node].push_back(parent);
                graph[parent].push_back(node);
            }

            build(node->left, node);
            build(node->right, node);
        };

    build(root, nullptr);

    int ans = 0;

    // BFS from every leaf
    for (TreeNode* src : leaves) {
        queue<pair<TreeNode*, int>> q;
        unordered_set<TreeNode*> visited;

        q.push({src, 0});
        visited.insert(src);

        while (!q.empty()) {
            auto [node, dist] = q.front();
            q.pop();

            if (dist > k)
                continue;

            // Another leaf found
            if (node != src &&
                !node->left && !node->right) {
                ans++;
            }

            if (dist == k)
                continue;

            for (TreeNode* nei : graph[node]) {
                if (!visited.count(nei)) {
                    visited.insert(nei);
                    q.push({nei, dist + 1});
                }
            }
        }
    }

    return ans / 2;
}

Let:
N = number of nodes
L = number of leaf nodes
K = given maximum distance

Building the graph:
Time: O(N)
Space: O(N)
Each BFS can visit at most O(N) nodes in the worst case, and we perform it for every leaf:
Time: O(L × N)
Since L can be O(N):
Worst-case time: O(N²)
The graph + BFS visited structures require:
Space: O(N)

So overall:
Time: O(N²)
Space: O(N)

----------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - 
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    int ans = 0;
    vector<int> helper(TreeNode* root, int d){
        if(!root) return {};
        if(!root -> left && !root -> right) return {1};

        vector<int> l = helper(root -> left, d);
        vector<int> r = helper(root -> right, d);


        for(int i : l){
            for(int j : r){
                if(i + j <= d) ans ++;
            }
        }

        vector<int> a;

        for(int i : l){
            if(i + 1 < d) a.push_back(i + 1);
        }

        for(int i : r){
            if(i + 1 < d) a.push_back(i + 1);
        }

        return a;

    }
public:
    int countPairs(TreeNode* root, int distance) {
        helper(root, distance);
        return ans;
    }
};

N = number of nodes, L = number of leaf nodes.
Time
DFS visits every node → O(N)
At each node:
Compare left and right leaf-distance vectors → O(L_left × L_right)
Across the whole tree, every pair of leaves is compared exactly once at their LCA.
Total leaf pairs → O(L²)
Worst case: O(N²)
Space
Recursion stack → O(N) worst case
Vectors storing leaf distances → O(N) worst case
Overall: O(N)

Final:
⏱️ Time: O(N²)
💾 Space: O(N)
