/*
Assignment 7 Q15
https://practice.geeksforgeeks.org/problems/min-distance-between-two-given-nodes-of-a-binary-tree/1

Given a binary tree with n nodes and two node values, a and b, your task is to find the minimum distance between them. The given two nodes are guaranteed to be in the binary tree and all node values are unique.

Examples :

Input: Tree = [1, 2, 3]
        1
      /  \
     2    3
a = 2, b = 3
Output: 2
Explanation: We need the distance between 2 and 3. Being at node 2, we need to take two steps ahead in order to reach node 3. The path followed will be: 2 -> 1 -> 3. Hence, the result is 2. 

Input: Tree = [11, 22, 33, 44, 55, 66, 77]
        11
      /   \
     22  33
    /  \  /  \
  44 55 66 77
a = 77, b = 22
Output: 3
Explanation: We need the distance between 77 and 22. Being at node 77, we need to take three steps ahead in order to reach node 22. The path followed will be: 77 -> 33 -> 11 -> 22. Hence, the result is 3.

Input: Tree = [1, 2, 3]
        1
      /  \
     2    3
a = 1, b = 3
Output: 1

Constraints:
2 <= number of nodes <= 10^5
*/

class Solution {
    Node* findLCA(Node* root, int a, int b){
        if(!root) return NULL;
        if(root -> data == a || root -> data == b) return root;
        
        Node* left = findLCA(root -> left, a, b);
        Node* right = findLCA(root -> right, a, b);
        
        if(!left) return right;
        else if(!right) return left;
        else return root;
    }
    
    int findDistFromLCA(Node* root, int a){
        if(!root) return -1;
        if(root -> data == a) return 0;
        
        int left = findDistFromLCA(root -> left, a);
        if(left != -1) return left + 1;
        
        int right = findDistFromLCA(root -> right, a);
        if(right != -1) return right + 1;
        
        return -1;
    }
    
  public:
    /* Should return minimum distance between a and b
    in a tree with given root*/
    int findDist(Node* root, int a, int b) {
        // Your code here
        Node* LCA = findLCA(root, a, b);
        int d1 = findDistFromLCA(LCA, a);
        int d2 = findDistFromLCA(LCA, b);
        
        return d1 + d2;
    }
};

TCA - O(N), SC - O(h)

--------------------------------------------------------------------------------------------------------------------------------------------

Above can be done using only one traversal

class Solution {
public:
    int ans = 0;

    int dfs(Node* root, int a, int b, int& distA, int& distB, int level) {
        if (!root) return -1;

        int left = dfs(root->left, a, b, distA, distB, level + 1);
        int right = dfs(root->right, a, b, distA, distB, level + 1);

        if (root->data == a) {
            distA = level;
            return root->data;
        }
        if (root->data == b) {
            distB = level;
            return root->data;
        }

        if (left != -1 && right != -1) {
            // This is the LCA
            ans = distA + distB - 2 * level;
            return root->data;
        }

        return (left != -1 || right != -1) ? root->data : -1;
    }

    int findDist(Node* root, int a, int b) {
        int distA = -1, distB = -1;
        dfs(root, a, b, distA, distB, 0);

        // If LCA was not found during traversal (edge case, when 1 node is ancestor of other node)
        if (ans == 0) ans = abs(distA - distB); 
        return ans;
    }
};
