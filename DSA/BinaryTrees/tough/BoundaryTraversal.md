/*
Given a Binary Tree, find its Boundary Traversal. The traversal should be in the following order: 

Left Boundary: This includes all the nodes on the path from the root to the leftmost leaf node. You must prefer the left child over the right child when traversing. Do not include leaf nodes in this section.

Leaf Nodes: All leaf nodes, in left-to-right order, that are not part of the left or right boundary.

Reverse Right Boundary: This includes all the nodes on the path from the rightmost leaf node to the root, traversed in reverse order. You must prefer the right child over the left child when traversing. Do not include the root in this section if it was already included in the left boundary.

Note: If the root doesn't have a left subtree or right subtree, then the root itself is the left or right boundary. 

Examples:

Input: root[] = [1, 2, 3, 4, 5, 6, 7, N, N, 8, 9, N, N, N, N]
Output: [1, 2, 4, 8, 9, 6, 7, 3]
 
Input: root[] = [1, 2, N, 4, 9, 6, 5, N, 3, N, N, N, N 7, 8]
Output: [1, 2, 4, 6, 5, 7, 8]
Explanation:
As the root doesn't have a right subtree, the right boundary is not included in the traversal.

Input: root[] = [1, N, 2, N, 3, N, 4, N, N] 
Output: [1, 4, 3, 2]
Explanation:
Left boundary: [1] (as there is no left subtree)
Leaf nodes: [4]
Right boundary: [3, 2] (in reverse order)
Final traversal: [1, 4, 3, 2]

Constraints:
1 ≤ number of nodes ≤ 10^5
1 ≤ node->data ≤ 10^5
*/

/*
// Tree Node
class Node {
  public:
    int data;
    Node* left;
    Node* right;

    // Constructor to initialize a new node
    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};
*/
bool isLeafNode(Node* node){
    return (!node -> left) && (!node -> right);
}

void leftBoundary(Node* root, vector<int>& ans){
    Node* temp = root -> left;
    while(temp){
        if(!isLeafNode(temp)) ans.push_back(temp -> data);
        if(temp -> left) temp = temp -> left;
        else temp = temp -> right;
    }
}

void leafNodesBoundary(Node* root, vector<int>& ans){
    if(!root) return;
    if(isLeafNode(root)) ans.push_back(root -> data);
    leafNodesBoundary(root -> left, ans);
    leafNodesBoundary(root -> right, ans);
}

void rightBoundary(Node* root, vector<int>& ans){
    stack<int> st;
    Node* temp = root -> right;
    while(temp){
        if(!isLeafNode(temp)) st.push(temp -> data);
        if(temp -> right) temp = temp -> right;
        else temp = temp -> left;
    }
    while(!st.empty()){
        ans.push_back(st.top());
        st.pop();
    }
}

class Solution {
  public:
    vector<int> boundaryTraversal(Node *root) {
        // code here
        vector<int> ans;
        if(!root) return ans;
        if(!isLeafNode(root)) ans.push_back(root -> data);
        leftBoundary(root, ans);
        leafNodesBoundary(root, ans);
        rightBoundary(root, ans);
        
        return ans;
        
    }
};