#include "LRUcache.cpp"
#include "LFUcache.cpp"
#include <iostream>
using namespace std;
class HybridCache {
private:
    int capacity;
    string mode;   // "LRU" or "LFU"
    LRUcache* lru;
    LFUcache* lfu;

public:
    HybridCache(int cap, string m) {
        capacity = cap;
        mode = m;
        if (mode == "LRU") lru = new LRUcache(cap);
        else if (mode == "LFU") lfu = new LFUcache(cap);
    }

    int get(int key) {
        if (mode == "LRU") return lru->get(key);
        else return lfu->get(key);
    }

    void put(int key, int val) {
        if (mode == "LRU") lru->put(key, val);
        else lfu->put(key, val);
    }

    void resize(int newcap) {
        if (mode == "LRU") lru->resize(newcap);
        else lfu->resize(newcap);
    }

    void printCache() {
        if (mode == "LRU") lru->printCache();
        else lfu->printCache();
    }
};
int main() {
    HybridCache cache(3, "LFU");  // or "LRU"
    cache.put(1, 100);
    cache.put(2, 200);
    cache.put(3, 300);
    cache.printCache();

    cout << "Get 2: " << cache.get(2) << endl;
    cache.printCache();

    cache.put(4, 400);
    cache.printCache();

    cache.resize(2);
    cache.printCache();

    return 0;
}
