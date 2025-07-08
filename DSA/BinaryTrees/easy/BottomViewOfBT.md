/*
https://www.geeksforgeeks.org/problems/bottom-view-of-binary-tree/1

Given a binary tree, return an array where elements represent the bottom view of the binary tree from left to right.

Note: If there are multiple bottom-most nodes for a horizontal distance from the root, then the later one in the level order traversal is considered. For example, in the below diagram, 7 and 34 both are the bottommost nodes at a horizontal distance of 0 from the root, here 34 will be considered.
For the above tree, the output should be 5 8 34 22 25

Examples :
Input: root[] = [1, 3, 2]
Output: [3 1 2]
Explanation: First case represents a tree with 3 nodes and 2 edges where root is 1, left child of 1 is 3 and right child of 1 is 2.
Thus bottom view of the binary tree will be 3 1 2.

Input: root[] = [10, 20, 30, 40, 60]         
Output: [40 20 60 30]

Constraints:
1 <= number of nodes <= 10^5
1 <= node->data <= 10^5
*/

class Solution {
  public:
    vector<int> bottomView(Node *root) {
        // Your Code Here
        vector<int> ans;
        if(!root) return ans;
        
        queue<pair<Node*, int>> q;
        map<int, int> nodes;
        
        q.push({root, 0});
        
        while(!q.empty()){
            pair<Node*, int> front = q.front();
            q.pop();
            Node* frontNode = front.first;
            int vertex = front.second;
            nodes[vertex] = frontNode -> data;
            
            if(frontNode -> left) q.push({frontNode -> left, vertex - 1});
            if(frontNode -> right) q.push({frontNode -> right, vertex + 1});
        }
        
        for(auto it : nodes){
            ans.push_back(it.second);
        }
        
        return ans;
    }
};

TC - O(NlogN), SC - O(N)