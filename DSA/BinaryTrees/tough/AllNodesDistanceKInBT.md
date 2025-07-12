/*
https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/description/

Given the root of a binary tree, the value of a target node target, and an integer k, return an array of the values of all nodes that have a distance k from the target node.
You can return the answer in any order.

Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
Output: [7,4,1]
Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.

Example 2:
Input: root = [1], target = 1, k = 3
Output: []

Constraints:
The number of nodes in the tree is in the range [1, 500].
0 <= Node.val <= 500
All the values Node.val are unique.
target is the value of one of the nodes in the tree.
0 <= k <= 1000
*/

Approach 1 - 2 BFS approach -> first get all the parents and then traverse in all directions -> left, right and top

class Solution {
    void mark_parent(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& parents){
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode* front = q.front();
            q.pop();
            if(front -> left){
                parents[front -> left] = front;
                q.push(front -> left);
            }
            if(front -> right){
                parents[front -> right] = front;
                q.push(front -> right);
            }
        }
    }
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        vector<int> ans;
        if(!root) return ans;
        unordered_map<TreeNode*, TreeNode*> parents;
        mark_parent(root, parents);

        unordered_set<TreeNode*> visited;
        int dist = 0;
        queue<TreeNode*> q;
        q.push(target);
        visited.insert(target);
        while(!q.empty() && dist < k){
            int qSize = q.size();
            for(int i = 0; i < qSize; i++){
                TreeNode* front = q.front();
                q.pop();
                if(front -> left && visited.count(front -> left) == 0){
                    q.push(front -> left);
                    visited.insert(front -> left);
                }
                if(front -> right && visited.count(front -> right) == 0){
                    q.push(front -> right);
                    visited.insert(front -> right);
                }
                if(parents.count(front) != 0 && visited.count(parents[front]) == 0){
                    q.push(parents[front]);
                    visited.insert(parents[front]);
                }
            }
            dist ++;
        }

        while(!q.empty()){
            ans.push_back(q.front() -> val);
            q.pop();
        }

        return ans;
    }
};


Approach 2 - make adj list and then do BFS

class Solution {
    void createAdj(unordered_map<int,vector<int>> &adj,TreeNode* root,unordered_map<int,bool> &visited){

        if ( !root ) return ;

        visited[root->val] = false ;

        if ( root->left ){
            adj[root->val].push_back(root->left->val) ;
            adj[root->left->val].push_back(root->val) ;
            createAdj(adj,root->left,visited) ;
        }

        if ( root->right ){
            adj[root->val].push_back(root->right->val) ;
            adj[root->right->val].push_back(root->val) ;
            createAdj(adj,root->right,visited) ;
        }

    }

    void dfs(vector<int> &answer,int start,int k,unordered_map<int,bool> &visited,unordered_map<int,vector<int>> &adj){
        visited[start] = true ;
        if ( k == 0 ){
            answer.push_back(start) ;
            return ;
        }
        for ( auto it : adj[start] ){
            if ( !visited[it] ){
                dfs(answer,it,k-1,visited,adj) ;
            }
        }
    }
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        
        if ( !root ) return {} ;
        unordered_map<int,vector<int>> adj ;
        unordered_map<int,bool> visited ;
        createAdj(adj,root,visited) ;

        vector<int> answer ;

        dfs(answer,target->val,k,visited,adj) ;

        return answer ;
    }
};