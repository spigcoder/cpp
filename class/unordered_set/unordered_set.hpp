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
    template<typename K>
    struct KofT{
        K operator()(const K& value) { return value; }
    };

    template<typename K, typename hash = HashFunc<K>>
    class unoredred_set{
    public:
        using iterator = typename Hash<K,K,KofT<K>,hash>::HashIterator;
        using const_iterator = typename Hash<K,K,KofT<K>,hash>::ConstHashIterator;
    public:
        pair<iterator,bool> insert(const K& key) { return _table.insert(key); }
        iterator begin() { return _table.begin(); }
        const_iterator begin() const { return _table.begin(); }
        const_iterator end() const { return _table.end(); }
        iterator end() { return _table.end(); }
        HashNode<K>* find(const K& key) { return _table.find(key); }
        bool erase(const K& key) { return _table.erase(key); }
    private:
        Hash<K, K, KofT<K>, hash> _table;
    };
};