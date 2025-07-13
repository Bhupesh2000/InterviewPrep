/*
https://leetcode.com/problems/two-sum-iv-input-is-a-bst/description/

Given the root of a binary search tree and an integer k, return true if there exist two elements in the BST such that their sum is equal to k, or false otherwise.

Example 1:
Input: root = [5,3,6,2,4,null,7], k = 9
Output: true

Example 2:
Input: root = [5,3,6,2,4,null,7], k = 28
Output: false

Constraints:
The number of nodes in the tree is in the range [1, 10^4].
-10^4 <= Node.val <= 10^4
root is guaranteed to be a valid binary search tree.
-10^5 <= k <= 10^5
*/

class BSTIterator {
public:
    stack<TreeNode*> st;
    bool reverse;

    BSTIterator(TreeNode* root, bool isReverse) {
        reverse = isReverse;
        pushAll(root);
    }

    int next() {
        TreeNode* node = st.top(); st.pop();
        if (reverse) pushAll(node->left);
        else pushAll(node->right);
        return node->val;
    }

    bool hasNext() {
        return !st.empty();
    }

private:
    void pushAll(TreeNode* node) {
        while (node) {
            st.push(node);
            node = reverse ? node->right : node->left;
        }
    }
};

class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        if (!root) return false;

        BSTIterator l(root, false);
        BSTIterator r(root, true);

        int i = l.next();
        int j = r.next();

        while (i < j) {
            int sum = i + j;
            if (sum == k) return true;
            else if (sum < k) {
                if (!l.hasNext()) break;
                i = l.next();
            } else {
                if (!r.hasNext()) break;
                j = r.next();
            }
        }

        return false;
    }
};