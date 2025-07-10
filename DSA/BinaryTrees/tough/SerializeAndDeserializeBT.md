/*
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

Clarification: The input/output format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

Example 1:
Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]

Example 2:
Input: root = []
Output: []

Constraints:
The number of nodes in the tree is in the range [0, 10^4].
-1000 <= Node.val <= 1000
*/

#include <sstream>

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root) return "";
        string ans = "";
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode* front = q.front();
            q.pop();
            if(!front) ans.append("#,");
            else{
                ans.append(to_string(front -> val) + ",");
                q.push(front -> left);
                q.push(front -> right);
            }
        }
        // cout << ans << endl;
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data == "") return nullptr;
        stringstream str(data);
        string s;

        getline(str, s, ',');
        TreeNode* root = new TreeNode(stoi(s));

        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode* front = q.front();
            q.pop();

            getline(str, s, ',');
            if(s == "#") front -> left = NULL;
            else{
                front -> left = new TreeNode(stoi(s));
                q.push(front -> left);
            }

            getline(str, s, ',');
            if(s == "#") front -> right = NULL;
            else{
                front -> right = new TreeNode(stoi(s));
                q.push(front -> right);
            }
        }

        return root;
    }
};