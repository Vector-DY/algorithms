#include <iostream>
#include <map>
#include <unistd.h>

using namespace std;

struct Node {
    int key;
    int val;
    time_t expireTime;
    Node *pre, *next;
    Node() : key(0), val(0), expireTime(time(nullptr)), pre(nullptr), next(nullptr) {}
    Node(int _key, int _val) : key(_key), val(_val), expireTime(time(nullptr)), pre(nullptr), next(nullptr) {}
    Node(int _key, int _val, time_t _expireTime) : key(_key), val(_val), expireTime(_expireTime), pre(nullptr), next(nullptr) {}
};

const int TTL = 1;

class LRUWithTTL 
{
private:
    int size;
    Node *head, *tail;
    map<int, Node*> mp;
public:
    LRUWithTTL(int capacity = 0)
    {
        size = capacity;
        head = nullptr;
        tail = nullptr;
    }

    void setHead(Node *node)
    {
        time_t curTime = time(nullptr);
        node->expireTime = curTime + TTL;
        node->next = head;
        node->pre = nullptr;
        if (head != nullptr) {
            head->pre = node;
        }
        head = node;
        if (tail == nullptr) {
            tail = node;
        }
    }

    void remove(Node *node) 
    {
        if (node->pre != nullptr) {
            node->pre->next = node->next;
        } else {
            head = node->next;
        }
        if (node->next != nullptr) {
            node->next->pre = node->pre;
        } else {
            tail = node->pre;
        }   
    }

    int get(int key)
    {
        auto it = mp.find(key);
        if (it != mp.end()) {
            Node *node = it->second;
            time_t curTime = time(nullptr);
            if (difftime(node->expireTime, curTime) <= 0) { // 过期返回-1
                remove(node);
                return -1;
            } else {
                remove(node);
                setHead(node);
                return node->val;
            }
        } else {
            return -1;
        }
    }

    void set(int key, int val)
    {
        auto it = mp.find(key);
        if (it != mp.end()) {
            Node *node = it->second;
            node->val = val;
            remove(node);
            setHead(node);
        } else {
            Node *newNode = new Node(key, val);
            if (mp.size() >= size) {
                time_t curTime = time(nullptr);
                map<int, Node*>::iterator it;
                for (it = mp.begin(); it != mp.end(); it++) {
                    if (difftime(it->second->expireTime, curTime) <= 0) {
                        break;
                    }
                }
                if (it != mp.end()) {
                    cout << "expire node : " << it->second->key;
                    cout << it->second->expireTime << endl;
                    remove(it->second);
                    mp.erase(it);
                } else {
                    remove(tail);
                    mp.erase(mp.find(tail->key));
                }
            }
            setHead(newNode);
            mp[key] = newNode;
        }
    }
    void print() 
    {
        for (auto it = mp.begin(); it != mp.end(); it++) {
            Node *node = it->second;
            cout << node->expireTime << endl;
        }
    }
};


int main()
{
    LRUWithTTL *lruCache = new LRUWithTTL(3);
    lruCache->set(2, 1);
    lruCache->set(1, 1);
    cout << lruCache->get(2) << endl;
    lruCache->set(4, 8);
    cout << lruCache->get(1) << endl;
    lruCache->set(4, 9);
    lruCache->set(4, 2);
    lruCache->set(4, 3);
    lruCache->set(4, 4);
    lruCache->set(4, 5);
    lruCache->set(4, 6);
    lruCache->set(4, 7);
    sleep(5);
    cout << lruCache->get(1) << endl;
    lruCache->set(6, 4);
    cout << time(nullptr) << endl;
    lruCache->print();
    return 0;
}