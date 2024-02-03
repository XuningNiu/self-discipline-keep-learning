/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        queue<Node*> q;

        if (root != nullptr)
            q.push(root);

        while (!q.empty()){
            int size = q.size();
            Node *pre = nullptr;

            for (int i = 0; i < size; i++){
                Node * cur = q.front(); q.pop();
                if (pre != nullptr){
                    pre->next = cur;
                }
                pre = cur;

                if (cur->left != nullptr && cur->right != nullptr){
                    q.push(cur->left);
                    q.push(cur->right);
                }
            }
        }
        return root;
    }
};