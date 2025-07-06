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
        cout << st2.top() -> val << " ";
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

--------------------------------------------------------------------------------------------------------------------------------------------

LevelOrder Traversal(level 1 -> level 2 -> .... -> level n)

// Iterative Method
void LevelOrderTraversalIterative(TreeNode* root){
    if(!root) return NULL;
    queue<TreeNode*> q;
    q.push(root);
    
    while(!q.empty()){
        TreeNode* front = q.front();
        q.pop();
        cout << front -> val << " ";
        if(front -> left) q.push(front -> left);
        if(front.right) q.push(front -> right);
    }
}

// Recursive Method -> TC - O(n^2), SC - O(h), O(N) in worst case, skewed tree
// Step 1: Get height of the tree
int getHeight(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

// Step 2: Print nodes at a given level
void printLevel(TreeNode* root, int level) {
    if (!root) return;
    if (level == 1) {
        cout << root->val << " ";
    } else {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

// Step 3: Level Order Traversal (Recursive)
void LevelOrderRecursive(TreeNode* root) {
    int height = getHeight(root);
    for (int i = 1; i <= height; ++i) {
        printLevel(root, i);
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------

Post, pre and inorder traversal in 1 go
Process : each stack entry will be a pair<TreeNode*, num(int)>
the num can be 1, 2, and 3.

Initially for each node num pushed will be 1.
If at the top,
num == 1, 
    push the TreeNode* to preOrder // because root is at position 1
    push again TreeNode* with num ++;
    if(top -> left) push pair{top -> left, 1}, left because after root, next is left

num == 2
    push the TreeNode* to inorder // because root is at position 2
    push again TreeNode* with num ++;
    if(top -> right) push pair{top -> right, 1}, left because after root, next is right

num == 3
    push the TreeNode* to postorder // because root is at position 3
    just pop


vector<vector<int>> TreeTraversals(TreeNode* root){
    vector<int> preOrder;
    vector<int> inOrder;
    vector<int> postOrder;
    vector<vector<int>> ans;
    
    if(!root){
        ans.push_back(preOrder);
        ans.push_back(inOrder);
        ans.push_back(postOrder);
        return ans;
    }
    
    stack<pair<TreeNode*, int>> st;
    st.push({root, 1});
    
    while(!st.empty()){
        pair<TreeNode*, int> p = st.top();
        st.pop();
        
        TreeNode* node = p.first;
        int num = p.second;
        
        if(num == 1){
            preOrder.push_back(node -> val);
            num ++;
            st.push({node, num});
            if(node -> left) st.push({node -> left, 1});
        }
        else if(num == 2){
            inOrder.push_back(node -> val);
            num ++;
            st.push({node, num});
            if(node -> right) st.push({node -> right, 1});
        }
        else{
            postOrder.push_back(node -> val);
        }
    }
    
    ans.push_back(preOrder);
    ans.push_back(inOrder);
    ans.push_back(postOrder);
    return ans;
}

TC - O(3 * N), SC - O(4 * N) -> 3 vectors, 1 stack