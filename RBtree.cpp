#include <stdexcept>

#include "RBtree.h"

template<typename KeyType,typename ValueType>
RBtree<KeyType,ValueType>::RBtree(){}

template<typename KeyType,typename ValueType>
RBtree<KeyType,ValueType>::~RBtree()
{
    if(this->root != nullptr){
        this->cleanup(this->root);
        this->root = nullptr;
    }
}

template<typename KeyType,typename ValueType>
void RBtree<KeyType,ValueType>::clear()
{
    if(this->root != nullptr){
        this->cleanup(this->root);
        this->root = nullptr;
    }
}

template<typename KeyType,typename ValueType>
bool RBtree<KeyType,ValueType>::hasKey(const KeyType& key)
{
    Node *node = this->root;
    while(node != nullptr){
        if(key == node->key){
            return true;
        }
        else if(key < node->key){
            node = node->left;
        }
        else{
            node = node->right;
        }
    }
    return false;
}


template<typename KeyType,typename ValueType>
ValueType& RBtree<KeyType,ValueType>::getValue(const KeyType& key)
{
    Node* node = root;
    while(node != nullptr){
        if(key == node->key){
            return node->data;
        }
        else if(key < node->key){
            node = node->left;
        }
        else{
            node = node->right;
        }
    }
    throw std::runtime_error("can not find the key");
}

template<typename KeyType,typename ValueType>
RBtree<KeyType,ValueType>& RBtree<KeyType,ValueType>::setValue(const KeyType& key,const ValueType& Value)
{
    Node *node = root;
    Node *parent = nullptr;
    // return directly if value exists
    while(node != nullptr){
        if(key == node->key){
            node->value = value;
            return *this;
        }
        else{
            parent = node;
            node = (key < node->key ? node->left : node->right);
        }
    }
    // create new node
    node = new Node;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->key = key;
    node->value = value;
    // set node as root if tree is NULL
    if(parent == nullptr){
        node->color = NodeColor::BLACK;
        this->root = node;
        return *this;
    }
    // 
    node->color = NodeColor::RED;
    if(key < parent->key){
        parent->left = node;
    }else{
        parent->right = node;
    }
    this->fixColorConflict(node);
    return *this;
}

template<typename KeyType,typename ValueType>
RBtree<KeyType,ValueType>& RBtree<KeyType,ValueType>::removeKey(const KeyType& key)
{
    Node *node = root;
    while(node != nullptr){
        if(key == node->key){
            break;
        }
        else{
            node = (key < node->key ? node->left : node->right);
        }
    }

    if(node == nullptr){
        throw std::runtime_error("can not find key");
    }
    // search replace node to delete
    while(node->left != nullptr || node->right != nullptr){
        if(node->right != nullptr){
            
        }
    }
}