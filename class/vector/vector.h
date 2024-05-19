#include<cstring>
#include <cstddef>
#include <functional>
#include<iostream>
#include <pthread.h>
#include<assert.h>
using namespace std;

namespace spigcoder {
	template<typename T>
	class vector{
	public:
		using value_type = T;
		using iterator = T*;
		using const_iterator = const T*;
		using reference = T&;
		using const_reference = const T&;
		using pointer = T*;
	
		//初始化列表是使用()进行初始化操作
		vector(): _start(nullptr), _finish(nullptr), _end_of_storage(nullptr){}
		template<typename T1>
		void destory(T1* pointer){
			pointer->~T1();
		}
		~vector(){ 
			delete[] _start;
		}
		vector(const vector& x);
		iterator begin(){ return _start; } 
		const_iterator begin() const { return _start; }
		iterator end() { return _finish; }
		const_iterator end() const { return _finish; } 
		size_t size() { return (size_t)(_finish - _start); }
		size_t capacity() { return (size_t)(_end_of_storage - _start); }
		reference operator[](size_t pos){ 
			assert(pos >= _start && pos < _finish); return _start[pos]; }
		vector& operator=(const vector& x);
		void reserve(size_t sz);
		void push_back(const T& x);
		iterator insert(iterator pos, const value_type val);
		iterator erase(iterator pos);
		const_reference operator[] (size_t pos) const{ 
			assert(pos >= _start && pos < _finish); return _start[pos]; }
		void swap(const T& x);
		
	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;
	};

	template<typename T>
	vector<T>::vector(const vector& x){
		reserve(x.capacity());	
		for(auto e : x){
			push_back(e);
		}
	}
	
	template<typename T>
	void vector<T>::swap(const T& x){
		std::swap(_start, x._start);	
		std::swap(_finish, x._finish);	
		std::swap(_end_of_storage, x._end_of_storage);	
	}

	template<typename T>
	vector<T>& vector<T>::operator=(const vector& x){
		vector<T> tmp;
		tmp.reserve(x.capacity());	
		for(auto e : x){
			tmp.push_back(e);
		}
		this->~vector();
		swap(tmp);
		return *this;
	}

	//使用模板定义与声明分离的化要在定义的前面加上模板
	template<typename T>
	void vector<T>::reserve(size_t sz){
		pointer tmp = new T[sz];
		size_t old_size = size();
		if(_start){
			//这里也不可以使用浅拷贝
			for(size_t i = 0; i < old_size; ++i){
				tmp[i] = _start[i];
			}
			//you should delete _start by youself
			delete[] _start;
		}
		_start = tmp;
		_finish = _start + old_size;
		_end_of_storage = _start + sz;	
	}

	template <typename T>
	void vector<T>::push_back(const T& x){
		if(_end_of_storage == _finish){
			size_t new_capacity = capacity() == 0 ? 4 : capacity() * 2;
			reserve(new_capacity);	
		}	
		*_finish = x;
		_finish++;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(iterator pos, const value_type val){
		//在使用insert时可能会出现迭代器失效的问题，因为如果需要进行扩容
		//那么_start就会发生改变，所以pos指向的就不再是一个有效的位置，所以要记录原来的位置
		//那有人就认为在iterator后面加一个&不就可以了，但我们在调用时通常都是insert(x.begin())
		//这时返回值时一个临时对象是不可以作为引用的右方的（如果加上const就无法对pos进行修改）
		//所以解决方法就是增加返回值
		size_t old_pos = pos - _start;
		if(_end_of_storage == _finish){
			size_t new_capacity = capacity() == 0 ? 4 : capacity() * 2;
			reserve(new_capacity);	
		}	
		pos = _start + old_pos;
		//移位 当然这里也可以使用指针进行操作
		size_t end = size();
		while(end >= old_pos + 1){
			_start[end] = _start[end - 1];
			end--;
		}
		*pos = val;
		_finish++;
		return _start + old_pos;
	} 
	
	template<typename T>
	//erase也会出现迭代器失效的问题，所以使用erase时也要注意更新迭代器
	typename vector<T>::iterator vector<T>::erase(iterator pos){
		size_t old_pos = pos - _start;
		assert(old_pos >= 0 && end() - pos > 0);
		iterator position = pos + 1;
		while(position <= _finish){
			*(position - 1) = *(position);
			position++;
		}
		--_finish;
		return _start + old_pos;	
	}
}	







