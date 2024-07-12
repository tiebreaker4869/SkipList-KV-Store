#pragma once

#include <cstring>
#include <vector>


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
Node<Key, Value>::Node(const Key k, const Value v, int l): 
key{k}, value{v}, level{l}, forward(l, nullptr) 
{
    
}

template<typename Key, typename Value>
Node<Key, Value>::~Node() {
    
}