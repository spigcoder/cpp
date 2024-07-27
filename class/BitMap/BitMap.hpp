#include <iostream>
using namespace std;

//这里是32是因为存储的值是int int是4个字节，然后每个字节8位
//大小是32个，所以可以存储的范围是32
constexpr size_t RANGE = 32;

template<size_t N>
class BitMap{
public:
    BitMap(){
        _bit_map.resize(N);
    }

    //将x对应的位设置为0
    void set(size_t x){
        //找出x是在第i个int中的第j位
        int i = x / RANGE;
        int j = x % RANGE;

        _bit_map[i] |= (1<<j); 
    }

    void unset(size_t x){
        //将x对应的位致0        
        int i = x / RANGE;
        int j = x % RANGE;

        _bit_map[i] &= ~(1<<j); 
    }

    bool test(size_t x){
        //判断x所在的位是不是1
        int i = x / RANGE;
        int j = x % RANGE;

        return _bit_map[i] & (1<<j);
    }

private:
    vector<int> _bit_map;
};


//使用位图还可以判断两个集合是否有元素相交 -> 就是说使用两个位图 
//分别表示 00 -> 只出现过一次 01 ->出现过1次 10->出现过2次 11->出现3次及以上
