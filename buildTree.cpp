#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode 
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


TreeNode* buildTree(const vector<int>& vec) 
{
    vector<TreeNode*> vecTree (vec.size(),nullptr);
    TreeNode* root = nullptr;
    for(int i = 0; i < vec.size(); i++) {
        TreeNode* node = nullptr;
        if(vec[i] != -1) {
            node = new TreeNode(vec[i]);
        }
        vecTree[i] = node;
        if(i == 0) {
            root = node;
        }
    }
    for(int i = 0; i * 2 + 1 < vec.size(); i++) {
        if(vecTree[i] != nullptr) {
            vecTree[i]->left = vecTree[i * 2 + 1];
            if(i * 2 + 2 < vec.size()) {
                vecTree[i]->right = vecTree[i * 2 + 2];
            }
        }
    }
    return root;
}

void print(TreeNode* root) 
{
    queue<TreeNode*> q;
    if(root != nullptr) {
        q.push(root);
    }
    vector<vector<int>> res;
    while(!q.empty()) {
        int size = q.size();
        vector<int> level;
        for(int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            if(node != nullptr) {
                level.push_back(node->val);
                q.push(node->left);
                q.push(node->right);
            }else {
                level.push_back(-1);
            }
        }
        res.push_back(level);
    }
    for(int i = 0; i < res.size(); i++) {
        for(int j = 0;j < res[i].size(); j++) {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    vector<int> a = {4,1,6,0,2,5,7,-1,-1,-1,3,-1,-1,-1,8};
    TreeNode* root = buildTree(a);
    print(root);

    return 0;
}