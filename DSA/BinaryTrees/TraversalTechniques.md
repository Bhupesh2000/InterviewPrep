class TreeNode{
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val){
        this -> val = val;
        this -> left = NULL;
        this -> right = NULL;
    }
};

PreOrder Traversal(root -> left -> right)

// Recursive Method
void PreOrderRecursive(TreeNode* root){
    if(!root) return;
    
    cout << root -> val << " ";
    PreOrderRecursive(root -> left);
    PreOrderRecursive(root -> right);
}

// Iterative Method
void PreOrderIterative(TreeNode* root){
    if(!root) return;
    stack<TreeNode*> st;
    st.push(root);
    
    while(!st.empty()){
        TreeNode* top = st.top();
        st.pop();
        cout << top -> val << " ";
        if(top -> right) st.push(top -> right);
        if(top -> left) st.push(top -> left);
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------

InOrder Traversal(left -> root -> right)

// Recursive Method 
void InOrderRecursive(TreeNode* root){
    if(!root) return;
    
    InOrderRecursive(root -> left);
    cout << root -> val << " ";
    InOrderRecursive(root -> right);
}

// Iterative Method
void InOrderIterative(TreeNode* root){
    if(!root) return;
    
    stack<TreeNode*> st;
    TreeNode* curr = root;
    while(curr || !st.empty()){
        while(curr){
            st.push(curr);
            curr = curr -> left;
        }
        curr = st.top();
        st.pop();
        cout << curr -> val << " ";
        curr = curr -> right;
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------

PostOrder Traversal(left -> right -> root)

// Recursive Method
void PostOrderRecursive(TreeNode* root){
    if(!root) return;
    
    PostOrderRecursive(root -> left);
    PostOrderRecursive(root -> right);
    cout << root -> val << " ";
}

// Iterative Method 1(Using 2 stacks)
void PostOrderIterative1(TreeNode* root){
    if(!root) return;
    stack<TreeNode*> st1, st2;
    
    st1.push(root);
    while(!st1.empty()){
        TreeNode* top = st1.top();
        st1.pop();
        st2.push(top);
        
        if(top -> left) st1.push(top -> left);
        if(top -> right) st1.push(top -> right);
    }
    
    while(!st2.empty()){
        cout << st2.top() << " ";
        st2.pop();
    }
}

// Iterative Method 2(Using 1 stack) -> less intitutive
void PostOrderIterative2(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode* curr = root;
    TreeNode* lastVisited = nullptr;

    while (curr || !st.empty()) {
        if (curr) {
            st.push(curr);
            curr = curr->left;
        } else {
            TreeNode* peekNode = st.top();
            if (peekNode->right && lastVisited != peekNode->right) {
                curr = peekNode->right;
            } else {
                cout << peekNode->val << " ";
                lastVisited = peekNode;
                st.pop();
            }
        }
    }
}
