#pragma once

#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>

template <typename Key, typename Value>
struct Node {

    Node() = default;

    Node(const Key& k, const Value& v, int l);

    ~Node();

    int level;
    std::vector<Node<Key, Value>*> forward;
    Key key;
    Value value;
};


template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& k, const Value& v, int l): 
key{k}, value{v}, level{l}, forward(l + 1, nullptr) 
{
    
}

template<typename Key, typename Value>
Node<Key, Value>::~Node() {
    
}


template<typename Key, typename Value>
class SkipList {
public:
    SkipList(int max_level);
    
    ~SkipList();
    
    int RandomHeight() const;

    void Insert(const Key& key, const Value& value);

    bool Contains(const Key& key) const;

    void Delete(const Key& key);

    void Display() const;

    int Size() const;

    void LoadFromFile(const std::string& filename);

    void DumpToFile(const std::string& filename);


private:
    int max_level_; // 最大 level
    int current_level_; // skiplist 当前的 level
    Node<Key, Value> head_; // 虚拟的头节点
    int num_element_; // 包含的实际节点的个数
    std::ifstream file_reader_; // 读文件
    std::ofstream file_writer_; // 写文件

    Node<Key, Value>* NewNode(const Key& key, const Value& value, const int level);

    void DeleteRecursively(const Key& key);
};

template <typename Key, typename Value>
SkipList<Key, Value>::SkipList(int max_level): 
max_level_{max_level}, current_level_{0}, head_{Key{}, Value{}, max_level},
num_element_{0} {

}


template <typename Key, typename Value>
SkipList<Key, Value>::~SkipList() {
    // TODO: implement destructor
}

template <typename Key, typename Value>
Node<Key, Value>* SkipList<Key, Value>::NewNode(const Key& key, const Value& value, const int level) {
    auto new_node = new Node<Key, Value>(key, value, level);
    return new_node;
}

template <typename Key, typename Value>
int SkipList<Key, Value>::RandomHeight() const {
    int level = 1;

    // 模拟抛硬币决定是否上升层级
    while (rand() % 2) {
        level ++;
    }

    // 不能超过最大 level
    level = std::min(level, max_level_);

    return level;
}

template <typename Key, typename Value>
bool SkipList<Key, Value>::Contains(const Key& key) const {
    auto current = &head_;

    for (int i = max_level_; i >= 0; i --) {
        // 在每一层尝试往前走, 走到头则下沉
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }

    // 看最后一层是否有要找的 key(所有的 key 在最后一层都会出现, 如果没有那就没有)
    current = current->forward[0];

    if (current && current->key == key) {
        return true;
    }

    return false;
}

template <typename Key, typename Value>
void SkipList<Key, Value>::Insert(const Key& key, const Value& value) {
    // TODO: implement insert
}