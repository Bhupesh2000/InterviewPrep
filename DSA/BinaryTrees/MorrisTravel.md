Inorder Morris Travel

class Solution {
  public:
    // Function to return a list containing the inorder traversal of the tree.
    vector<int> inOrder(Node* root) {
        Node* curr = root;
        vector<int> ans;
        while(curr){
            if(!curr -> left){
                ans.push_back(curr -> data);
                curr = curr -> right;
            }
            else{
                Node* prev = curr -> left;
                while(prev -> right && prev -> right != curr){
                    prev = prev -> right;
                }
                if(!prev -> right){
                    prev -> right = curr;
                    curr = curr -> left;
                }
                else{
                    prev -> right = NULL;
                    ans.push_back(curr -> data);
                    curr = curr -> right;
                }
            }
        }
        return ans;
    }
};

TC - O(N), SC - O(1)

Preorder Morris Travel

class Solution {
  public:
    // Function to return a list containing the preorder traversal of the tree.
    vector<int> preOrder(Node* root) {
        Node* curr = root;
        vector<int> ans;
        while(curr){
            if(!curr -> left){
                ans.push_back(curr -> data);
                curr = curr -> right;
            }
            else{
                Node* prev = curr -> left;
                while(prev -> right && prev -> right != curr){
                    prev = prev -> right;
                }
                if(!prev -> right){
                    prev -> right = curr;
                    ans.push_back(curr -> data);
                    curr = curr -> left;
                }
                else{
                    prev -> right = NULL;
                    curr = curr -> right;
                }
            }
        }
        return ans;
    }
};