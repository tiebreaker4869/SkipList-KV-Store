#pragma once

#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <iostream>

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
    SkipList(const SkipList&) = delete;

    SkipList& operator=(const SkipList&) = delete;

    SkipList();
    
    ~SkipList();
    
    int RandomHeight() const;

    bool Insert(const Key& key, const Value& value);

    bool Contains(const Key& key) const;

    const Value* Get(const Key& key) const;

    void Delete(const Key& key);

    void Display() const;

    int Size() const;

    void LoadFromFile(const std::string& filename);

    void DumpToFile(const std::string& filename);


private:
    enum {kMaxLevel = 13};// 最大 level
    int current_level_; // skiplist 当前的 level
    Node<Key, Value> head_; // 虚拟的头节点
    int num_element_; // 包含的实际节点的个数

    Node<Key, Value>* NewNode(const Key& key, const Value& value, const int level);

    void DeleteRecursively(const Key& key);
};

template <typename Key, typename Value>
SkipList<Key, Value>::SkipList(): current_level_{0}, head_{Key{}, Value{}, kMaxLevel},
num_element_{0} {

}


template <typename Key, typename Value>
SkipList<Key, Value>::~SkipList() {
    auto current = head_.forward[0];
    while (current) {
        auto next = current->forward[0];
        delete current;
        current = next;
    }
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
    while (rand() % 2 && level < kMaxLevel) {
        level ++;
    }

    return level;
}

template <typename Key, typename Value>
const Value* SkipList<Key, Value>::Get(const Key& key) const {
    auto current = &head_;

    for (int i = current_level_; i >= 0; i --) {
        // 在每一层尝试往前走, 走到头则下沉
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }

    // 看最后一层是否有要找的 key(所有的 key 在最后一层都会出现, 如果没有那就没有)
    current = current->forward[0];

    if (current && current->key == key) {
        return &current->value;
    }

    return nullptr;
}

template <typename Key, typename Value>
bool SkipList<Key, Value>::Contains(const Key& key) const {
    return Get(key) != nullptr;
}

template <typename Key, typename Value>
bool SkipList<Key, Value>::Insert(const Key& key, const Value& value) {
    auto current = &head_;

    std::vector<Node<Key, Value>*> updated(kMaxLevel + 1, nullptr);

    for (int i = current_level_; i >= 0; i --) {
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        updated[i] = current;
    }

    current = current->forward[0];

    // 待插入的 key 已经存在
    if (current && current->key == key) {
        return false;
    }

    // 插入过程
    int level = RandomHeight();

    // 如果插入的节点 level 大于当前 level
    if (level > current_level_) {
        for (int i = current_level_ + 1; i <= level; i ++) {
            updated[i] = &head_;
        }

        current_level_ = level;
    }

    // 创建新节点
    auto node = NewNode(key, value, level);

    // 在各层插入新节点, 更新 forward 指针
    for (int i = 0; i <= level; i ++) {
        node->forward[i] = updated[i]->forward[i];
        updated[i]->forward[i] = node;
    }

    num_element_ ++;

    return true;
}

template <typename Key, typename Value>
int SkipList<Key, Value>::Size() const {
    return num_element_;
}

template <typename Key, typename Value>
void SkipList<Key, Value>::Delete(const Key& key) {
    auto current = &head_;
    std::vector<Node<Key, Value>*> updated(kMaxLevel + 1, nullptr);

    for (int i = current_level_; i >= 0; i --) {
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        // 记录在每一层可能的前驱
        updated[i] = current;
    }

    // 是否找到待删除节点
    current = current->forward[0];
    if (current == nullptr || current->key != key) {
        return;
    }

    // 只有在 0 - node 的 level 之间 node 有前驱
    for (int i = 0; i <= current->level; i ++) {
        updated[i]->forward[i] = current->forward[i];
    }

    // 调整当前 skiplist 整体 level
    while (current_level_ > 0 && head_.forward[current_level_] == nullptr) {
        current_level_ --;
    }

    delete current;

    num_element_ --;
}

template <typename Key, typename Value>
void SkipList<Key, Value>::Display() const {
    for (int i = current_level_; i >= 0; i --) {
        std::cout << "Level " << i << ":";

        auto current = head_.forward[i];
        while (current) {
            std::cout << "(" << current->key << ", " << current->value << ") ";
            current = current->forward[i];
        }

        // 本层输出结束
        std::cout << std::endl;
    }
}

template <typename Key, typename Value>
void SkipList<Key, Value>::LoadFromFile(const std::string& filename) {

}

template <typename Key, typename Value>
void SkipList<Key, Value>::DumpToFile(const std::string& filename) {
    
}