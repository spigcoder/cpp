#include "RBTree.hpp"

template<typename K>
class set{
public:
    struct KeyOfValue{
        const K& operator()(const K& key){
            return key;
        }
    };

    using iterator = typename RBTree<K, K, KeyOfValue>::iterator;

    iterator begin(){
        return _t.begin();
    }


    iterator end(){
        return _t.end();
    }

    bool insert(const K& key){
        return _t.insert(key);
    }

private:
    RBTree<K, K, KeyOfValue> _t;
};