#pragma once
#include <vector>
#include <memory>
#include <optional>
#include <iostream>
using namespace std;
//使用开散列来实现hash

//声明Hash
template<typename K, typename V, typename KofT, typename hash>
class Hash;

template<typename V>
struct HashNode{
    HashNode(const V& data)
    :_data(data),
    _next(nullptr)
    {}

    V _data;
    shared_ptr<HashNode> _next;
};

template<typename K, typename Ref, typename Ptr, typename KofT, typename hash>
struct Iterator{
    using Node = HashNode<K>;
    using Self = Iterator<K,Ref,Ptr,KofT,hash>;

    Iterator(const Hash<K,K,KofT,hash>* table, shared_ptr<Node> node)
    :_node(node), hash_table(table)
    {}

    Self& operator++(){
        hash hs;
        KofT kot;
        //如果这个桶里还有元素，就返回这个元素的下一个
        if(_node->_next){
            _node = _node->_next;
            return *this;
        }
        size_t sz = hash_table->_table.size(), hashi = hs(kot(_node->_data)) % sz;
        hashi++;
        if(hashi == sz) _node = nullptr;
        for(size_t i = hashi; i < sz; ++i){
            if(hash_table->_table[i]){
                _node = hash_table->_table[i];
                break;
            }
        }
        return *this;
    }

    Ref operator*(){
        return _node->_data;
    }

    Ptr operator->(){
        return &operator*();
    }

    bool operator!=(const Self& it){
        return it._node != _node;
    }

    bool operator==(const Self& it){
        return it._node == _node;
    }

    shared_ptr<Node> _node;
    //这里最好使用指针，如果使用Hash的话会有一次拷贝构造，从而降低效率
    const Hash<K, K, KofT, hash>* hash_table; //用来寻找下一个节点
};

template<typename K, typename V, typename KofT, typename hash>
class Hash{
private:
    template<typename InK, typename Ref, typename Ptr, typename InKofT, typename Inhash>
    friend struct Iterator;
    using Node = HashNode<V>;
public:
    using HashIterator = Iterator<K, K&, K*, KofT, hash>;
    using ConstHashIterator = Iterator<K, const K&, const K*, KofT, hash>;
public:
    Hash():_n(0) { _table.resize(10); }
    Hash(const Hash<K,V,KofT,hash>& table){
        size_t sz = table._table.size();
        _table.resize(sz);
        for(int i = 0; i < sz; ++i){
            shared_ptr<Node> cur = table._table[i];
            shared_ptr<Node> prev;
            while(cur){
                shared_ptr<Node> new_node = make_shared<Node>(cur->_data);
                if(!prev){
                    _table[i] = move(new_node);
                    prev = _table[i];
                }else{
                    prev->_next = move(new_node);
                    prev = prev->_next;
                }
                cur = cur->_next;
            }
        }
    }
    HashIterator begin(){
        size_t sz = _table.size();
        for(int i = 0; i < sz; ++i){
            if(_table[i]) return HashIterator(this, _table[i]);
        }
        return end();
    }

    ConstHashIterator begin() const{
        size_t sz = _table.size();
        for(int i = 0; i < sz; ++i){
            if(_table[i]) return HashIterator(this, _table[i]);
        }
        return end();
    }

    HashIterator end(){
        return HashIterator(this, nullptr);
    }

    ConstHashIterator end() const{
        return HashIterator(this, nullptr);
    }

    pair<HashIterator, bool> insert(const V& kv);
    HashIterator find(const K& key); 
    bool erase(const K& key);
private:
    vector<shared_ptr<Node>> _table;
    size_t _n = 0;              //记录插入的个数，可以用来计算平衡因子
};

template<typename K, typename V, typename KofT, typename hash>
typename Hash<K,V,KofT,hash>::HashIterator Hash<K, V, KofT, hash>::find(const K& key){
    hash hs;
    KofT kot;
    size_t sz = _table.size(), hashi = hs(key) % sz; 
    //当这个桶执行的元素历遍完了，如果还是没有找到就证明没有这个元素
    shared_ptr<Node> cur = _table[hashi];
    while(cur){
        if(kot(cur->_data) == key) return HashIterator(this, cur);
        else cur = (cur->_next);
    }
    return HashIterator(this, nullptr);
}

//这里扩容时有一个效率的问题，就是我们是像开放定址法一样新创建一个_table
//然后逐渐进行插入吗，如果是这样的化，那么效率太低，所以可以重复利用原来创建好的指针
template<typename K, typename V, typename KofT, typename hash>
pair<typename Hash<K,V,KofT,hash>::HashIterator, bool> Hash<K,V,KofT,hash>::insert(const V& kv){
    hash hs;
    KofT kot;
    HashIterator node = find(kot(kv));
    if(node != end()) return {node, false};
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
                size_t hashi = hs(kot(cur->_data)) % new_sz;
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
    size_t hashi = hs(kot(kv)) % _table.size();
    shared_ptr<Node> old_node = _table[hashi];
    shared_ptr<Node> new_node = make_shared<Node>(kv);
    new_node->_next = move(old_node);
    _table[hashi] = move(new_node);
    _n++;
    return {HashIterator(this, new_node), true};
}

template<typename K, typename V, typename KofT, typename hash>
bool Hash<K,V,KofT,hash>::erase(const K& key){
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














