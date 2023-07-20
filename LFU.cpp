#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

struct Node {
    int key, val, freq;
    Node(int _key, int _val, int _freq) : key(_key), val(_val), freq(_freq) {}
};


class LFUCache {
private:
    int minfreq, size;
    unordered_map<int, list<Node>::iterator> key_table;
    unordered_map<int, list<Node>> freq_table;
public:
    LFUCache(int capacity) {
        minfreq = 0;
        size = capacity;
        key_table.clear();
        freq_table.clear();
    }

    int get(int key) {
        if (size == 0) {
            return -1;
        }
        auto it = key_table.find(key);
        if (it == key_table.end()) {
            return -1;
        }
        list<Node>::iterator node = it->second;
        int val = node->val, freq = node->freq;
        freq_table[freq].erase(node);
        // erase blank list
        if (freq_table[freq].size() == 0) {
            freq_table.erase(freq);
            if (minfreq == freq) {
                minfreq += 1;
            }
        }
        // insert to freq + 1
        freq_table[freq + 1].push_front(Node(key, val, freq + 1));
        key_table[key] = freq_table[freq + 1].begin();
        return val;
    }

    void put(int key, int value) {
        if (size == 0) {
            return ;
        }
        auto it = key_table.find(key);
        if (it == key_table.end()) {
            // cache full
            if (key_table.size() == size) {
                auto iter = freq_table[minfreq].back();
                key_table.erase(iter.key);
                freq_table[minfreq].pop_back();
                if (freq_table[minfreq].size() == 0) {
                    freq_table.erase(minfreq);
                }
            }
            freq_table[1].push_front(Node(key, value, 1));
            key_table[key] = freq_table[1].begin();
            minfreq = 1;
        } else {
            list<Node>::iterator node = it->second;
            int freq = node->freq;
            freq_table[freq].erase(node);
            if (freq_table[freq].size() == 0) {
                freq_table.erase(freq);
                if (minfreq == freq) {
                    minfreq += 1;
                }
            }
            freq_table[freq + 1].push_front(Node(key, value, freq + 1));
            key_table[key] = freq_table[freq + 1].begin();
        }
    }
};

int main()
{
    LFUCache *lfu = new LFUCache(2);
    lfu->put(1, 1);
    lfu->put(2, 2);
    cout << lfu->get(1) << endl;
    lfu->put(3,3);
    cout << lfu->get(2) << endl;
    cout << lfu->get(3) << endl;
    lfu->put(4, 4);
    cout << lfu->get(1) << endl;
    cout << lfu->get(3) << endl;
    cout << lfu->get(4) << endl;
    return 0;
}