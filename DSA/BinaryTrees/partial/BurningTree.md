/*
Assignment 7 Q24
https://www.geeksforgeeks.org/problems/burning-tree/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=burning-tree

Given a binary tree and a target node, determine the minimum time required to burn the entire tree if the target node is set on fire. In one second, the fire spreads from a node to its left child, right child, and parent.
Note: The tree contains unique values.

Examples : 
Input: root[] = [1, 2, 3, 4, 5, 6, 7], target = 
Output: 3
Explanation: Initially 2 is set to fire at 0 sec 
At 1 sec: Nodes 4, 5, 1 catches fire.
At 2 sec: Node 3 catches fire.
At 3 sec: Nodes 6, 7 catches fire.
It takes 3s to burn the complete tree.

Input: root[] = [1, 2, 3, 4, 5, N, 7, 8, N, 10], target = 10
Output: 5
Explanation: Initially 10 is set to fire at 0 sec 
At 1 sec: Node 5 catches fire.
At 2 sec: Node 2 catches fire.
At 3 sec: Nodes 1 and 4 catches fire.
At 4 sec: Node 3 and 8 catches fire.
At 5 sec: Node 7 catches fire.
It takes 5s to burn the complete tree.

Constraints:
1 ≤ number of nodes ≤ 10^5
1 ≤ node->data ≤ 10^5
*/

class Solution {
    void makeParent(Node* root, unordered_map<Node*, Node*>& parent){
        queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            Node* front = q.front();
            q.pop();
            if(front -> left){
                parent[front -> left] = front;
                q.push(front -> left);
            }
            if(front -> right){
                parent[front -> right] = front;
                q.push(front -> right);
            }
        }
    }
    
    Node* findTarget(Node* root, int target){
        if(!root) return NULL;
        if(root -> data == target) return root;
        Node* leftAns = findTarget(root -> left, target);
        if(!leftAns) return findTarget(root -> right, target);
        return leftAns;
    }
    
  public:
    int minTime(Node* root, int target) {
        // code here
        if(!root) return 0;
        unordered_map<Node*, Node*> parent;
        makeParent(root, parent);
        
        int time = 0;
        Node* t = findTarget(root, target);
        if(!t) return 0;
        
        unordered_set<Node*> visited;
        queue<Node*> q;
        q.push(t);
        visited.insert(t);
        while(!q.empty()){
            int qSize = q.size();
            for(int i = 0; i < qSize; i++){
                Node* front = q.front();
                q.pop();
                if(front -> left && visited.count(front -> left) == 0){
                    q.push(front -> left);
                    visited.insert(front -> left);
                }
                if(front -> right && visited.count(front -> right) == 0){
                    q.push(front -> right);
                    visited.insert(front -> right);
                }
                if(parent.count(front) != 0 && visited.count(parent[front]) == 0){
                    q.push(parent[front]);
                    visited.insert(parent[front]);
                }
            }
            time ++;
        }
        return time - 1;
    }
};

