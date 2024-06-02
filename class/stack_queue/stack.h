#pragma once
#include<deque>

//容器适配器的思想，对其他的容器进行包装从而得到我们想要的内容
namespace spigcoder{
    template<class T, class Container = std::deque<T>>
    class stack{
    public:
        void push(const T& val){
            _con.push_back(val);
        }

        void pop(){
            _con.pop_back();
        }
        
        T& top(){
            return _con.back();
        }

        size_t size(){
            return _con.size();
        }

        bool empty(){
            return _con.empty();
        }

    private:
        Container _con;
    };
}