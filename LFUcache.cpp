
#include <bits/stdc++.h>
using namespace std;
struct LFUnode
{
    int key, val, freq;
    LFUnode *prev;
    LFUnode *next;
    LFUnode(int k, int v)
    {
        key = k;
        val = v;
        freq = 1;
        prev = next = NULL;
    }
};
class doublyll
{
public:
    LFUnode *head;
    LFUnode *tail;
    int size;
    doublyll()
    {
        head = new LFUnode(-1, -1);
        tail = new LFUnode(-1, -1);
        head->next = tail;
        tail->prev = head;
        size = 0;
    }
    void addToFront(LFUnode *node)
    {

        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
        size++;
    }
    void removeNode(LFUnode *node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        size--;
       
    }
    LFUnode *removeLast()
    {
        if (size == 0)
            return NULL;
        LFUnode *prev = tail->prev;
        removeNode(prev);
        return prev;
    }
    void printList()
    {
        LFUnode *curr = head->next;
        while (curr != tail)
        {
            cout << "(" << curr->key << "," << curr->val << "," << curr->freq << ")";
            curr = curr->next;
        }
    }
};
class LFUcache
{
private:
    int capacity;
    int minfreq;
    unordered_map<int, LFUnode *> keymap;
    unordered_map<int, doublyll *> freqmap;
    void updateFreq(LFUnode *node)
    {
        int f = node->freq;
        freqmap[f]->removeNode(node);
        if (f == minfreq && freqmap[f]->size == 0)
        {
            minfreq++;
        }
        node->freq++;
        if (freqmap.find(node->freq) == freqmap.end())
        {
            freqmap[node->freq] = new doublyll();
        }
        freqmap[node->freq]->addToFront(node);
    }

public:
    LFUcache(int cap)
    {
        capacity = cap;
        minfreq = 0;
    }
    int get(int key)
    {
        if (keymap.find(key) == keymap.end())
            return -1;
        LFUnode *node = keymap[key];
        updateFreq(node);
        return node->val;
    }
    void put(int key, int val)
    {
        if (capacity == 0)
            return;
        if (keymap.find(key) != keymap.end())
        {
            LFUnode *node = keymap[key];
            node->val = val;
            updateFreq(node);
            return;
        }
        if (keymap.size() >= capacity)
        {
            LFUnode *victim = freqmap[minfreq]->removeLast();
            keymap.erase(victim->key);
            delete victim;
        }
        LFUnode *node = new LFUnode(key, val);
        minfreq = 1;
        if (freqmap.find(1) == freqmap.end())
        {
            freqmap[1] = new doublyll();
        }
        freqmap[1]->addToFront(node);
        keymap[key] = node;
    }
    void resize(int newcap)
    {
        capacity = newcap;
        while (keymap.size() > capacity)
        {
            LFUnode *victim = freqmap[minfreq]->removeLast();
            keymap.erase(victim->key);
            delete victim;
        }
    }
    void printCache()
    {
        cout << "LFU cache content by frequency: " << endl;
      for (auto it = freqmap.begin(); it != freqmap.end(); ++it)
{
    int freqy = it->first;
    doublyll* listy = it->second;
    cout << "frequency " << freqy << ": ";
    listy->printList();
    cout << endl;
}

        cout << endl;
    }
};

int main()
{
      LFUcache cache(3);

    cache.put(1, 100);
    cache.put(2, 200);
    cache.put(3, 300);
    cache.printCache();

    cout << "Get 2: " << cache.get(2) << endl;  // increases freq of 2
    cache.printCache();

    cache.put(4, 400);  // should evict key 1 (freq 1, LRU)
    cache.printCache();

    cache.put(2, 250);  // update value and freq
    cache.printCache();

    cache.resize(2);     // reduce capacity to 2
    cache.printCache();
    return 0;
}
