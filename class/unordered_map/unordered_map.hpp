#include "Hash.hpp"

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

namespace spigcoder{    
    template<typename K, typename V>
    struct KofT{
        K operator()(const pair<K, V>& value) { return value.first; }
    };

    template<typename K, typename V, typename hash = HashFunc<K>>
    class unoredred_map{
    public:
        using iterator = typename Hash<K,pair<K,V>,KofT<K,V>,hash>::HashIterator;
        using const_iterator = typename Hash<K,pair<K,V>,KofT<K,V>,hash>::ConstHashIterator;
    public:
        pair<iterator,bool> insert(const pair<K,V>& kv) { return _table.insert(kv); }
        iterator begin() { return _table.begin(); }
        const_iterator begin() const { return _table.begin(); }
        const_iterator end() const { return _table.end(); }
        iterator end() { return _table.end(); }
        HashNode<K>* find(const K& key) { return _table.find(key); }
        bool erase(const K& key) { return _table.erase(key); }
    private:
        Hash<K, pair<K,V>, KofT<K,V>, hash> _table;
    };
};