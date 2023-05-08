#include <iostream>
#include <string>
#include <string.h>

using namespace std;
const int MaxBranchNum = 26;

class TrieNode{
public:
    string word;
    int path;
    int end;
    TrieNode* next[MaxBranchNum];

    TrieNode()
    {
        word = "";
        path = 0;
        end = 0;
        memset(next,NULL,sizeof(TrieNode*) * MaxBranchNum);
    }
};


class TrieTree{
private:
    TrieNode *root;
public:
    TrieTree();
    ~TrieTree();
    void insert(string str);
    int search(string str);
    void deleteStr(string str);
    void destory(TrieNode* root);
    void printTrie();
    void printPre(string str);
    void printStr(TrieNode* root);
    int prefixNumbers(string str);
};

TrieTree::TrieTree()
{
    root = new TrieNode();
}

TrieTree::~TrieTree()
{
    destory(root);
}

void TrieTree::destory(TrieNode* root)
{
    if(root == nullptr){
        return ;
    }
    for(int i = 0;i < MaxBranchNum;i++){
        destory(root->next[i]);
    }
    delete(root);
    root = nullptr;
}

void TrieTree::insert(string str)
{
    if(str == ""){
        return ;
    }
    string s(str);
    TrieNode* node = root;
    int index = 0;
    for(int i = 0;i < s.size();i++){
        index = s[i] - 'a';
        if(node->next[index] == nullptr){
            node->next[index] = new TrieNode();
        }
        node = node->next[index];
        node->path++;
    }   
    node->end++;
    node->word = str;
}

int TrieTree::search(string str)
{
    if(str == ""){
        return 0;
    }
    string s(str);
    TrieNode* node = root;
    int index = 0;
    for(int i = 0;i < s.size();i++){
        index = s[i] - 'a';
        if(node->next[index] == nullptr){
            return 0;
        }
        node = node->next[index];
    }
    if(node != nullptr){
        return node->end;
    }
    else{
        return 0;
    }
}

void TrieTree::deleteStr(string str)
{
    if(str == ""){
        return ;
    }
    string s(str);
    TrieNode* node = root;
    TrieNode* tmp;
    int index = 0;
    for(int i = 0;i < s.size();i++){
        index = s[i] - 'a';
        tmp = node->next[index];
        if(--node->next[index]->path == 0){
            delete node->next[index];
        }
        node = tmp;
    }
    node->end--;
}

int TrieTree::prefixNumbers(string str)
{
    if(str == ""){
        return 0;
    }
    string s(str);
    TrieNode *node = root;
    int index = 0;
    for(int i = 0;i < s.size();i++){
        index = s[i] - 'a';
        if(node->next[index] == nullptr){
            return 0;
        }
        node = node->next[index];
    }
    return node->path;
}

void TrieTree::printPre(string str)
{
    if(str == ""){
        return ;
    }
    string s(str);
    TrieNode* node = root;
    int index = 0;
    for(int i = 0;i < s.size();i++){
        index = s[i] - 'a';
        if(node->next[index] == nullptr){
            return ;
        }
        node = node->next[index];
    }
    printStr(node);
}

void TrieTree::printStr(TrieNode* node)
{
    if(node == nullptr){
        return ;
    }
    if(node->word != ""){
        cout<<node->word<<" "<<node->path<<endl;
    }
    for(int i = 0;i < MaxBranchNum;i++){
        printStr(node->next[i]);
    }
}

void TrieTree::printTrie()
{
    printStr(root);
}


int main()
{
    TrieTree trie;
    string str = "dingding";
    cout<<trie.search(str)<<endl;
    trie.insert(str);
    trie.insert("dinga");
    trie.insert("dingc");
    trie.insert("dingab");
    trie.insert("dingad");
    trie.printPre("dinga");
    trie.deleteStr("dinga");
    trie.printTrie();
    return 0;  


}
