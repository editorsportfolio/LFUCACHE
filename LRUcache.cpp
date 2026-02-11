#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int value;
    int key;
    Node *prev;
    Node *next;
    Node(int k, int v)
    {
        key = k;
        value = v;
        prev = NULL;
        next = NULL;
    }
};
class doubly
{
public:
    Node *head;
    Node *tail;
    doubly()
    {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }
    void addToFront(Node *node)
    {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
    void removeNode(Node *node)
    {
        Node *p = node->prev;
        Node *n = node->next;
        p->next = n;
        n->prev = p;
    }
    void moveToFront(Node *node)
    {
        removeNode(node);
        addToFront(node);
    }
    Node *removeLast()
    { //                                             [ remove LRU node ]
        if (tail->prev == head)
            return nullptr; // empty list
        Node *last = tail->prev;
        removeNode(last);
        return last;
    }
    void printList()
    {
        Node *curr = head->next;
        while (curr != tail)
        {
            cout << "(" << curr->key << "," << curr->value << ")" << " ";
            curr = curr->next;
        }
        cout << endl;
    }
};
class LRUcache
{
private:
    int capacity;
    unordered_map<int, Node *> cache;
    doubly dll;

public:
    LRUcache(int cap)
    {
        capacity = cap;
    }
    int get(int key)
    {
        if (cache.find(key) == cache.end())
            return -1; // not found

        // if found
        Node *node = cache[key];
        dll.moveToFront(node);
        return node->value;
    }
    void put(int key, int value)
    {
        if (cache.find(key) != cache.end())
        {
            Node *node = cache[key];
            node->value = value;
            dll.moveToFront(node);
        }
        else
        {
            if (cache.size() >= capacity)
            {
                Node *lru = dll.removeLast();
                if (lru)
                {
                    cache.erase(key);
                }
            }
            Node *node =new Node(key, value);
            dll.addToFront(node);
            cache[key] = node;
        }

    }
    void printCache()
    {
        dll.printList();
    }
    void resize(int newcap){
capacity=newcap;
while(cache.size()>capacity){
    Node* lru=dll.removeLast();
    if(lru){
        cache.erase(lru->key);
        delete lru;
    }
}
    }
};

int main()
{

    // doubly dll;
    // Node *n1 = new Node(1, 10);
    // Node *n2 = new Node(2, 20);
    // Node *n3 = new Node(3, 30);
    // dll.printList();
    // dll.addToFront(n1);
    // dll.addToFront(n2);
    // dll.addToFront(n3);
    // dll.printList();
    // dll.moveToFront(n2);
    // dll.printList();
    // dll.removeNode(n1);
    // dll.printList();
    LRUcache cache(3);
 cache.put(1,100);
 cache.put(2,200);
  cache.put(3,300);
  cache.printCache();
    cout << "Get 2: " << cache.get(2) << endl;   
    cache.printCache(); // (2,200) (3,300) (1,100)
    cache.put(4, 400);  
    cache.printCache();  
    cout << "Get 1: " << cache.get(1) << endl; // -1, evicted
    cache.put(2, 250);  
    cache.printCache();  
     cache.resize(2);
      cache.printCache();  

    return 0;
}