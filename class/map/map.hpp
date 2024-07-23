#pragma once 
#include "RBTree.hpp"

template<typename K, typename V>
class map{
public:
    struct KeyOfValue{
        K operator()(const pair<K, V>& kv){
            return kv.first;
        }
    };

    using iterator = typename RBTree<K, pair<K,V>, KeyOfValue>::iterator;

    iterator begin(){
        return _t.begin();
    }


    iterator end(){
        return _t.end();
    }

    pair<bool, iterator> insert(const pair<K,V>& key){
        return _t.insert(key);
    }

    V& operator[](const K& key){
        pair<bool, iterator> it = _t.insert({key, V()});
        return (it.second)->second;
    }

private:
    RBTree<K, pair<K,V>, KeyOfValue> _t;
};