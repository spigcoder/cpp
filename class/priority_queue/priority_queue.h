#include<vector>
#include<functional>
#include<algorithm>
using namespace std;


namespace spigcoder{
//Compare是一个仿函数 -> 类 + operator()(argument) 
template<class T, class Container = std::vector<T>, class Compare = std::greater<int>>
    class priority_queue{
    public:
        priority_queue() = default;
        template<class InputIterator>
        priority_queue(InputIterator first, InputIterator last){
            //这里有一点知识是要知道的就是在构造是，堆向下调整的时间复杂度是N
            //向上调整的时间复杂度是logN*N
            while(first != last){
                _con.push_back(*first);
                ++first;
            }
            //向下调整
            for(int i = (_con.size()-1-1) / 2; i >= 0; --i){
                AdjustDown(i);
            }
        }

        void AdjustUp(int child){
            int parent = (child - 1) / 2;
            while(child > 0){
                if(Compare()(_con[parent], _con[child])){
                    swap(_con[child], _con[parent]);
                    child = parent;
                    parent = (child - 1) / 2;
                }else{
                    break;
                }
            }
        }

        void AdjustDown(int parent){
            int child = parent*2 + 1;
            //当孩子出界时就可以结束了
            while(child < _con.size()){
                //找出较大的孩子
                if(child + 1 < _con.size() && Compare()(_con[child], _con[child + 1]))
                    child++;
                if(Compare()(_con[parent], _con[child])){
                    swap(_con[child], _con[parent]);
                    parent = child;
                    child = parent*2 + 1;
                }else{
                    break;
                }
            }
        }

        void push(const T& val){
            _con.push_back(val);
            AdjustUp(_con.size() - 1);
        }

        void pop(){
            swap(_con.front(), _con.back());
            _con.pop_back();
            AdjustDown(0);
        }

        size_t size(){
            return _con.size();
        }

        bool empty(){
            return _con.empty();
        }

        T& top(){
            return _con.front();
        }

    private:
        Container _con;
    };
}