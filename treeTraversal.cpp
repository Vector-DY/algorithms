#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
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

/*递归遍历*/
/*先序*/
void preorder(TreeNode *root, vector<int> &res) {
    if (root == nullptr) {
        return ;
    }
    res.push_back(root->val);
    preorder(root->left, res);
    preorder(root->right, res);
}
/*中序*/
void inorder(TreeNode *root, vector<int> &res) {
    if (root == nullptr) {
        return ;
    }
    inorder(root->left, res);
    res.push_back(root->val);
    inorder(root->right, res);
}
/*后序*/
void postorder(TreeNode *root, vector<int> &res) {
    if (root == nullptr) {
        return ;
    }
    postorder(root->left, res);
    postorder(root->right, res);
    res.push_back(root->val);
}

/*迭代遍历*/
/*先序*/
vector<int> preorderStk(TreeNode *root) {
    vector<int> res;
    if (root == nullptr) {
        return res;
    }
    stack<TreeNode*> stk;
    TreeNode *node = root;
    while (node != nullptr || !stk.empty()) {
        while (node != nullptr) {
            res.push_back(node->val);
            stk.push(node);
            node = node->left;
        }
        node = stk.top();
        stk.pop();
        node = node->right;
    }
    return res;
}
/*中序*/
vector<int> inorderStk(TreeNode *root) {
    vector<int> res;
    if (root == nullptr) {
        return res;
    }
    stack<TreeNode*> stk;
    TreeNode *node = root;
    while (node != nullptr || !stk.empty()) {
        while (node != nullptr) {
            stk.push(node);
            node = node->left;
        }
        node = stk.top();
        stk.pop();
        res.push_back(node->val);
        node = node->right;
    }
    return res;
}
/*后序*/
vector<int> postorderStk(TreeNode *root) {
    vector<int> res;
    if (root == nullptr) {
        return res;
    }
    stack<TreeNode*> stk;
    TreeNode *node = root;
    while (node != nullptr || !stk.empty()) {
        while (node != nullptr) {
            res.push_back(node->val);
            stk.push(node);
            node = node->right;
        }
        node = stk.top();
        stk.pop();
        node = node->left;
    }
    reverse(res.begin(), res.end());
    return res;
} 

/*Morris遍历*/
/*先序*/
vector<int> preorderTraversal(TreeNode *root) {
    vector<int> res;
    if (root == nullptr) {
        return res;
    }

    TreeNode *p1 = root, *p2 = nullptr;

    while (p1 != nullptr) {
        p2 = p1->left;
        if (p2 != nullptr) {
            while (p2->right != nullptr && p2->right != p1) {
                p2 = p2->right;
            }
            if (p2->right == nullptr) {
                res.emplace_back(p1->val);
                p2->right = p1;
                p1 = p1->left;
                continue;
            } else {
                p2->right = nullptr;
            }
        } else {
            res.emplace_back(p1->val);
        }
        p1 = p1->right;
    }
    return res;
}

/*中序*/
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    TreeNode *predecessor = nullptr;

    while (root != nullptr) {
        if (root->left != nullptr) {
            // predecessor 节点就是当前 root 节点向左走一步，然后一直向右走至无法走为止
            predecessor = root->left;
            while (predecessor->right != nullptr && predecessor->right != root) {
                predecessor = predecessor->right;
            }
            
            // 让 predecessor 的右指针指向 root，继续遍历左子树
            if (predecessor->right == nullptr) {
                predecessor->right = root;
                root = root->left;
            }
            // 说明左子树已经访问完了，我们需要断开链接
            else {
                res.push_back(root->val);
                predecessor->right = nullptr;
                root = root->right;
            }
        }
        // 如果没有左孩子，则直接访问右孩子
        else {
            res.push_back(root->val);
            root = root->right;
        }
    }
    return res;
}

/*后序*/
void addPath(vector<int> &vec, TreeNode *node) {
    int count = 0;
    while (node != nullptr) {
        ++count;
        vec.emplace_back(node->val);
        node = node->right;
    }
    reverse(vec.end() - count, vec.end());
}

vector<int> postorderTraversal(TreeNode *root) {
    vector<int> res;
    if (root == nullptr) {
        return res;
    }

    TreeNode *p1 = root, *p2 = nullptr;

    while (p1 != nullptr) {
        p2 = p1->left;
        if (p2 != nullptr) {
            while (p2->right != nullptr && p2->right != p1) {
                p2 = p2->right;
            }
            if (p2->right == nullptr) {
                p2->right = p1;
                p1 = p1->left;
                continue;
            } else {
                p2->right = nullptr;
                addPath(res, p1->left);
            }
        }
        p1 = p1->right;
    }
    addPath(res, root);
    return res;
}

int main(int argc, char* argv[])
{
    vector<int> a = {4,1,6,0,2,5,7,-1,-1,-1,3,-1,-1,-1,8};
    TreeNode* root = buildTree(a);
    vector<int> pre, in, post;
    preorder(root, pre);
    inorder(root, in);
    postorder(root, post);
    for (int i = 0; i < pre.size(); i++) {
        cout << pre[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < in.size(); i++) {
        cout << in[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < post.size(); i++) {
        cout << post[i] << " ";
    }
    cout << endl;
    pre = preorderStk(root);
    in = inorderStk(root);
    post = postorderStk(root);
    for (int i = 0; i < pre.size(); i++) {
        cout << pre[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < in.size(); i++) {
        cout << in[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < post.size(); i++) {
        cout << post[i] << " ";
    }
    cout << endl;
    pre = preorderTraversal(root);
    in = inorderTraversal(root);
    post = postorderTraversal(root);
    for (int i = 0; i < pre.size(); i++) {
        cout << pre[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < in.size(); i++) {
        cout << in[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < post.size(); i++) {
        cout << post[i] << " ";
    }
    cout << endl;
    return 0;
}