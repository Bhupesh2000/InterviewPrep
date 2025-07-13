/*
Given an arbitrary binary tree, your task is to convert it to a binary tree that holds Children Sum Property, by incrementing the data values of any node.

Note: The structure of the tree can't be changed and the node values can't be decremented. Also, there exist multiple possible answers.

Example:
Input:   50
           /   \    
       7         2
   /     \     /   \
  3      5  1      30
Output: 50
             /   \    
         19       31 
     /    \      /   \
  14      5  1      30
Explanation: For every node, now its value is equal to the sum of values of its immediate left and right child. One more possible solution is:

               79
             /   \    
         48       31 
     /    \      /   \
  43      5  1      30

*/

Approach 1

#include <iostream>

using namespace std;

class TreeNode{
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val){
        this -> val = val;
        left = right = NULL;
    }
};

void increment(TreeNode* curr, int diff){
    if(curr -> left){
        curr -> left -> val += diff;
        increment(curr -> left, diff);
    }
    else if(curr -> right){
        curr -> right -> val += diff;
        increment(curr -> right, diff);
    }
}

void convertTree(TreeNode* root){
    if(!root || (!root -> left && !root -> right)) return;
    
    convertTree(root -> left); 
    convertTree(root -> right); 
    
    int leftValue = 0, rightValue = 0;
    if(root -> left) leftValue = root -> left -> val;
    if(root -> right) rightValue = root -> right -> val;
    
    
    int diff = root -> val - (leftValue + rightValue);
    
    // root Node value is lesser
    if(diff < 0){
        root -> val += abs(diff);
    }
    // root Node is greater
    else if(diff > 0){
        increment(root, abs(diff));
    }
}

// prints the inorder traversal of tree
void printInorder(TreeNode* cur)  { 
    if (cur == nullptr) 
        return; 
    
    printInorder(cur->left); 
    cout<<cur->val<<" ";
    printInorder(cur->right); 
} 

int main()  { 
    // construct the binary tree
    /*
        50
       /  \     
      7    2
     / \  / \
    3   5 1  30    */
    
    TreeNode *root = new TreeNode(50); 
    root->left = new TreeNode(7); 
    root->right = new TreeNode(2); 
    root->left->left = new TreeNode(3); 
    root->left->right = new TreeNode(5); 
    root->right->left = new TreeNode(1); 
    root->right->right = new TreeNode(30); 
    printInorder(root);
    cout << endl;
    convertTree(root); 
    
    printInorder(root); 
    return 0; 
}

TC - O(N^2), SC - O(h)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 -> first go from top to down and increase the value of child of each node if leftSum + rightSum < root -> val. this ensures that child will be always be greater than equal to root -> val.
next go from bottom to up and set the value of root of the sum of left and right child.

#include <iostream>

using namespace std;

class TreeNode{
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val){
        this -> val = val;
        left = right = NULL;
    }
};

void convertTree(TreeNode* root){
    if(!root || (!root -> left && !root -> right)) return;
    
    int leftData = 0, rightData = 0;
    if(root -> left) leftData = root -> left -> val;
    if(root -> right) rightData = root -> right -> val;
    
    if(leftData + rightData < root -> val){
        if(root -> left) root -> left -> val = root -> val;
        if(root -> right) root -> right -> val = root -> val;
    }
    
    convertTree(root -> left);
    convertTree(root -> right);
    
    int tot = 0;
    if(root -> left) tot += root -> left -> val;
    if(root -> right) tot += root -> right -> val;
    
    if(tot != 0) root -> val = tot;
    
}

void printInorder(TreeNode* cur)  { 
    if (cur == nullptr) 
        return; 
    
    printInorder(cur -> left); 
    cout<< cur -> val << " ";
    printInorder(cur -> right); 
} 

int main()  { 
    // construct the binary tree
    /*
        50
       /  \     
      7    2
     / \  / \
    3   5 1  30    */
    
    TreeNode *root = new TreeNode(50); 
    root->left = new TreeNode(7); 
    root->right = new TreeNode(2); 
    root->left->left = new TreeNode(3); 
    root->left->right = new TreeNode(5); 
    root->right->left = new TreeNode(1); 
    root->right->right = new TreeNode(30); 
    printInorder(root);
    cout<<endl;

    convertTree(root); 
    
    printInorder(root); 
    return 0; 
}

TC - O(N), SC - O(N)