#include <iostream>
#include <string>
#include <vector>

using Color = bool;
using KEY_TYPE = int;
using VALUE_TYPE = int;

static const Color red = false;
static const Color black = true;

class RBtree_node {
public:
    Color color;
    RBtree_node *parent;
    RBtree_node *left;
    RBtree_node *right;

    KEY_TYPE key;
    VALUE_TYPE value;
    RBtree_node(Color color_) : color(color_), parent(nullptr), left(nullptr), right(nullptr),key(-1e5) {}
    RBtree_node(Color color_, KEY_TYPE key_, RBtree_node *nil) : color(color_), parent(nil), left(nil), right(nil), key(key_) {}
};

class RBtree {
private:
    RBtree_node *root;
    RBtree_node *nil;

public:
    RBtree() {
        nil = new RBtree_node(black);
        root = nil;
    }

    void leftRotate(RBtree_node *left_node);

    void rightRotate(RBtree_node *right_node);

    void insertNode(KEY_TYPE key);

    void fixInsert(RBtree_node *node);

    RBtree_node *searchNode(KEY_TYPE key);

    RBtree_node *successor(RBtree_node *node);

    void deteleNode(KEY_TYPE key);

    void fixDelete(RBtree_node *node);

    void print();

    void printMiddle(RBtree_node *node);
};

void RBtree::leftRotate(RBtree_node *left_node) {
    RBtree_node *right_node = left_node->right;
    left_node->right = right_node->left;

    if (right_node->left != nil) {
        left_node->right->parent = left_node;
    }
    right_node->parent = left_node->parent;
    if (left_node == root) {
        root = right_node;
    } else if (left_node == left_node->parent->left) {
        left_node->parent->left = right_node;
    } else {
        left_node->parent->right = right_node;
    }

    left_node->parent = right_node;
    right_node->left = left_node;
}

void RBtree::rightRotate(RBtree_node *right_node) {
    RBtree_node *left_node = right_node->left;
    right_node->left = left_node->right;

    if (left_node->right != nil) {
        right_node->left->parent = right_node;
    }
    left_node->parent = right_node->parent;
    if (right_node == root) {
        root = left_node;
    } else if (right_node == right_node->parent->right) {
        right_node->parent->right = left_node;
    } else {
        right_node->parent->right = right_node;
    }
    right_node->parent = left_node;
    left_node->right = right_node;
}
