/*
Assignment 7 Q12
https://leetcode.com/problems/count-complete-tree-nodes/

Given the root of a complete binary tree, return the number of the nodes in the tree.
According to Wikipedia, every level, except possibly the last, is completely filled in a complete binary tree, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
Design an algorithm that runs in less than O(n) time complexity.

Example 1:
Input: root = [1,2,3,4,5,6]
Output: 6

Example 2:
Input: root = []
Output: 0

Example 3:
Input: root = [1]
Output: 1

Constraints:
The number of nodes in the tree is in the range [0, 5 * 10^4].
0 <= Node.val <= 5 * 10^4
The tree is guaranteed to be complete.
*/

Approach 1 - using any traversal technique and counting for each node
TC - O(N), SC - O(h) -> logN, because of complete binary tree

Approach 2 - 
no of nodes in a fully complete tree with n level - 2^n - 1
So only last level will have partial number of nodes.
Get leftmost height and rightmost height. 
    if lh == rh for any node, that means that tree is fully complete
    else check for its children

class Solution {
public:
    int countNodes(TreeNode* root) {
        if(!root) return 0;

        int lh = leftHeight(root);
        int rh = rightHeight(root);

        if(lh == rh) return (1 << lh) - 1;
        return countNodes(root -> left) + countNodes(root -> right) + 1;
    }

    int leftHeight(TreeNode* root){
        TreeNode* temp = root;
        int cnt = 0;
        while(temp){
            cnt ++;
            temp = temp ->left;
        }
        return cnt;
    }

    int rightHeight(TreeNode* root){
        TreeNode* temp = root;
        int cnt = 0;
        while(temp){
            cnt ++;
            temp = temp ->right;
        }
        return cnt;
    }
};

🔍 Time Complexity Analysis
Step-by-step:
Height Calculation:
leftHeight() and rightHeight() both take O(log N) time in a complete binary tree (height is log N).

Perfect Tree Check:
If leftHeight == rightHeight, the tree is perfect → can return node count directly in O(1).

Recursive Case:
If not perfect, recurse into left and right children.

⚠️ Key Insight:
Even though the function recurses, we only recurse into one subtree per level, not both — unless the subtree is not perfect.
At each level:
You do O(log N) work to compute heights.
There are at most log N levels.
So it's not a full O(N) traversal like a brute-force solution.

✅ Final Time Complexity:
O((log N)²)
At each level of recursion (at most log N levels),
you do O(log N) work (height calculation),
so total is O(log N × log N) = O((log N)²).

🧾 Space Complexity:
O(log N) for recursive call stack depth (tree height).

| Part              | Complexity      |
| ----------------- | --------------- |
| Time              | **O((log N)²)** |
| Space (recursion) | **O(log N)**    |
