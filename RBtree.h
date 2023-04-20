#pragma once

template<typename KeyType, typename ValueType>
class RBtree{
public:
    RBtree();
    ~RBtree();

    void clear(); // clear all the elements

    bool hasKey(const KeyType& queryKey); // search key

    ValueType& getValue(const KeyType& key); // search value by key

    RBtree<KeyType, ValueType>& setValue(const KeyType& key,const ValueType& data);

    RBtree<KeyType, ValueType>& removeKey(const KeyType& key);

private:
    enum class NodeColor {
        RED, BLACK
    };
    enum class ChildSide{
        LEFT,RIGHT;
    }
    struct Node{
        KeyType key;
        ValueType value;
        NodeColor color = NodeColor::RED;
        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;
    };

    void cleanup(Node* node);

    void leftRotate(Node* node);

    void rightRotate(Node* node);

    void fixColorConflict(Node* node);

    void fixUnbalanced(Node* node);

    Node* root = nullptr;
};