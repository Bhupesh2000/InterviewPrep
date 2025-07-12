/*
Assignment 7 Q10
https://practice.geeksforgeeks.org/problems/binary-tree-to-dll/1

Given a Binary Tree (BT), convert it to a Doubly Linked List (DLL) in place. The left and right pointers in nodes will be used as previous and next pointers respectively in converted DLL. The order of nodes in DLL must be the same as the order of the given Binary Tree. The first node of Inorder traversal (leftmost node in BT) must be the head node of the DLL.
Note: h is the tree's height, and this space is used implicitly for the recursion stack.

TreeToList
Examples:
Input:
      1
    /  \
   3    2
Output:
3 1 2 
2 1 3
Explanation: DLL would be 3<=>1<=>2

Input:
       10
      /   \
     20   30
   /   \
  40   60
Output:
40 20 60 10 30 
30 10 60 20 40
Explanation:  DLL would be 40<=>20<=>60<=>10<=>30.

Constraints:
1 ≤ Number of nodes ≤ 105
0 ≤ Data of a node ≤ 105
*/

class Solution {
    pair<Node*, Node*> bToDLLHelper(Node* root){
        if(!root) return {NULL, NULL};
        pair<Node*, Node*> leftAns = bToDLLHelper(root -> left);
        Node* leftHead = leftAns.first;
        Node* leftTail = leftAns.second;
        
        if(leftTail) leftTail -> right = root;
        root -> left = leftTail;
        
        pair<Node*, Node*> rightAns = bToDLLHelper(root -> right);
        Node* rightHead = rightAns.first;
        Node* rightTail = rightAns.second;
        
        root -> right = rightHead;
        if(rightHead) rightHead -> left = root;
        
        Node* head = (leftHead) ? leftHead : root;
        Node* tail = (rightTail) ? rightTail : root;
        
        return {head, tail};
    }
  public:
    Node* bToDLL(Node* root) {
        // code here
        pair<Node*, Node*> ans = bToDLLHelper(root);
        return ans.first;
    }
};