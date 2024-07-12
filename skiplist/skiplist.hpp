#pragma once

#include <cstring>
#include <vector>
#include <fstream>


template <typename Key, typename Value>
struct Node {

    Node() = default;

    Node(const Key k, const Value v, int l);

    ~Node();

    int level;
    std::vector<Node<Key, Value>*> forward;
    Key key;
    Value value;
};

template<typename Key, typename Value>
class SkipList {
public:
    SkipList(int max_level);
    
    ~SkipList();
    
    int RandomHeight() const;

    int Insert(const Key& key, const Value& value);

    Value Search(const Key& key) const;

    bool Contains(const Key& key) const;

    void Delete(const Key& key);

    void Display() const;

    int Size() const;

    void LoadFromFile(const std::string& filename);

    void DumpToFile(const std::string& filename);


private:
    int max_level_; // 最大 level
    int current_level; // skiplist 当前的 level
    Node<Key, Value> head_; // 虚拟的头节点
    int num_element_; // 包含的实际节点的个数
    std::ifstream file_reader_; // 读文件
    std::ofstream file_writer_; // 写文件

    Node<Key, Value>* NewNode(const Key& key, const Value& value, const int level);

    void DeleteRecursively(const Key& key);
};


template<typename Key, typename Value>
Node<Key, Value>::Node(const Key k, const Value v, int l): 
key{k}, value{v}, level{l}, forward(l + 1, nullptr) 
{
    
}

template<typename Key, typename Value>
Node<Key, Value>::~Node() {
    
}