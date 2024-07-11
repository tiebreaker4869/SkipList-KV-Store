#pragma once

#include <cstring>


template <typename Key, typename Value>
struct Node {

    Node() = default;

    Node(const Key k, const Value v, int l);

    ~Node();

    int level;
    Node<Key, Value>* forward;
    Key key;
    Value value;
};


template<typename Key, typename Value>
Node<Key, Value>::Node(const Key k, const Value v, int l): 
key{k}, value{v}, level{l}, forward{new Node<Key, Value>[l + 1]} 
{
    memset(forward, 0, sizeof(void*) * (l + 1));
}

template<typename Key, typename Value>
Node<Key, Value>::~Node() {
    delete[] forward;
}