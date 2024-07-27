#pragma once
#include <vector>
#include <memory>
#include <optional>
#include <iostream>
using namespace std;

template <typename T>
struct HashFunc{
    size_t operator()(const T& key){
        return (size_t)key;
    }
};

//模板的特化
template<> 
struct HashFunc<string>{
    size_t operator()(const string& key){
        size_t num = 0;
        for(auto e : key){
            num += e;
            num *= 31;
        }
        return num;
    }
};
//使用开放定址法（闭散列）实现哈希表
namespace openaddress{
    enum State{
        EXIST,
        EMPTY,
        DELETE
    };

    template<typename K, typename V> struct HashNode{
        HashNode() = default;
        HashNode(const pair<K, V>& kv)
        :_kv(kv),
        _state(EMPTY)
        {}

        pair<K, V> _kv;
        State _state = EMPTY; 
    };

    template<typename K, typename V, typename hash = HashFunc<K>>
    class Hash{
    private:
        using Node = HashNode<K, V>;
    public:
        Hash(){ _hash.resize(10); }
        bool erase(const K& key);
        Node* find(const K& key);
        bool insert(const pair<K, V>& kv);

    private:
        vector<Node> _hash;
        size_t _n = 0; //c++的默认构造函数对于自定义类型是不会进行初始化操作的，所以这个要自己来进行初始化
    };

    template<typename K, typename V, typename hash>
    bool Hash<K, V, hash>::insert(const pair<K, V>& kv){
        //去重
        if(find(kv.first)) return false;
        //使用除留余数法进行数据的定位
        hash hs;
        if(_n / (double)_hash.size() >= 0.7){
            //进行扩容，扩容时不能直接对_hash进行resize因为扩容之后sz发生了变化映射关系也就发生了变化
            //所以合适的扩容方法是新建一个表，然后把旧的数据重新插入到新表当中，然后进行vector的交换
            Hash<K,V, hash> new_hash;
            new_hash._hash.resize(2*_hash.size());
            for(int i = 0; i < _hash.size(); ++i){
                if(_hash[i]._state == EXIST){
                    pair<K,V> l_kv = _hash[i]._kv;
                    new_hash.insert(l_kv);
                }
            } 
            _hash.swap(new_hash._hash);
        }

        //插入操作
        size_t sz = _hash.size();
        size_t hashi = hs(kv.first) % sz;
        while(_hash[hashi]._state == EXIST){
            hashi = (hashi+1)%sz;
        }
        _hash[hashi]._kv = kv;
        _hash[hashi]._state = EXIST;
        ++_n;
        return true;
    }

    template<typename K, typename V, typename hash>
    typename Hash<K, V, hash>::Node* Hash<K, V, hash>::find(const K& key){
        hash hs;
        size_t sz = _hash.size();
        size_t hashi = hs(key) % sz;
        while(_hash[hashi]._state != EMPTY){
            if (_hash[hashi]._state == EXIST && _hash[hashi]._kv.first == key){
                return &_hash[hashi];
            }
            hashi = (++hashi)%sz;
        }
        return nullptr;
    }

};

//使用开散列来实现hash
namespace openlist{
    template<typename K, typename V>
    struct HashNode{
        HashNode(const pair<K, V>& data)
        :_data(data),
        _next(nullptr)
        {}

        pair<K, V> _data;
        shared_ptr<HashNode> _next;
    };

    template<typename K, typename V, typename hash = HashFunc<K>>
    class Hash{
    private:
        using Node = HashNode<K,V>;
    public:
        Hash():_n(0) { _table.resize(10); }
        bool insert(const pair<K, V>& kv);
        Node* find(const K& key); 
        bool erase(const K& key);
    private:
        vector<shared_ptr<Node>> _table;
        size_t _n = 0;              //记录插入的个数，可以用来计算平衡因子
    };
    template<typename K, typename V, typename hash>
    HashNode<K,V>* Hash<K, V, hash>::find(const K& key){
        hash hs;
        size_t sz = _table.size(), hashi = hs(key) % sz; 
        //当这个桶执行的元素历遍完了，如果还是没有找到就证明没有这个元素
        shared_ptr<Node> cur = _table[hashi];
        while(cur){
            if(cur->_data.first == key) return HashIterator(this, cur);
            else cur = (cur->_next);
        }
        return HashIterator(this, nullptr);
    }

    //这里扩容时有一个效率的问题，就是我们是像开放定址法一样新创建一个_table
    //然后逐渐进行插入吗，如果是这样的化，那么效率太低，所以可以重复利用原来创建好的指针
    template<typename K, typename V, typename hash>
    bool Hash<K,V,hash>::insert(const pair<K, V>& kv){
        HashIterator node = find(kv.first);
        if(node) ;
        hash hs;
        size_t old_sz = _table.size();
        //当桶中元素的数量和桶的数量相同时进行扩容操作
        if(_n == old_sz){
            size_t new_sz = old_sz*2;
            vector<shared_ptr<Node>> new_table;
            new_table.resize(new_sz);
            for(int i = 0; i < old_sz; ++i){
                //unique<Node>
                auto cur = _table[i];
                while(cur){
                    size_t hashi = hs(cur->_data.first) % new_sz;
                    auto next = (cur->_next);
                    shared_ptr<Node> ptr = new_table[hashi];
                    cur->_next = ptr;
                    new_table[hashi] = move(cur);
                    cur = next;
                }
            }
            _table.swap(new_table);
        } 
        //插入新节点
        size_t hashi = hs(kv.first) % _table.size();
        shared_ptr<Node> old_node = _table[hashi];
        shared_ptr<Node> new_node = make_shared<Node>(kv);
        new_node->_next = move(old_node);
        _table[hashi] = move(new_node);
        _n++;
    }

    template<typename K, typename V, typename hash>
    bool Hash<K,V,hash>::erase(const K& key){
        hash hs;
        size_t sz = _table.size(), hashi = hs(key)%sz;
        shared_ptr<Node> cur = _table[hashi];
        shared_ptr<Node> prev;
        while(cur){
            if(cur->_data.first == key){
                if(!prev) {
                    _table[hashi] = move(cur->_next);
                }
                else{
                    prev->_next = move(cur->_next);
                }
                return true;
            }
            prev = cur;
            cur = cur->_next;
        } 
        return false;
    }
}













