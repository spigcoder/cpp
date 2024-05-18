#include"string.h"
#include <cassert>
#include <sys/types.h>

//相同的命名空间会在链接阶段进行合并
namespace spig{
	//static成员变量在类外面声明，如果有多个文件则不要在.h文件中进行声明
	//否则会造成连接错误
	const size_t string::npos = -1;
	//缺省参数如果定义与声明分离，在声明处给缺省参数
	string::string(const char* str)
	:_size(strlen(str))
	{
		_str = new char[_size + 1];	
		strcpy(_str, str);
		_capacity = _size;
	}
	
	string::~string(){
		delete [] _str;
		_str = nullptr;
		_size = _capacity = 0;
	}

	//还有一种写法是使用构造函数来帮助我们完成拷贝构造
	string::string(const string& s){
//		char* tmp = new char[s._capacity + 1];	
//		strcpy(tmp, s._str);
//		_str = tmp;
//		_size = s._size;
//		_capacity = s._capacity;
		string tmp(s._str);
		swap(tmp);
	}

	string& string::operator=(const string& s){
		//由于我们并不知道要赋值的内容到底是多大的
		//是比当前的容量大，大很多，还是小，或者小很多
		//有几种方法可以解决1.是进行较为仔细的判断然后分类
		//或者可以直接进行拷贝，然后将之前的内容删除
//		char* tmp = new char[s._capacity + 1];
//		strcpy(tmp, s._str);
	//	delete[] _str;
	//	_str = tmp;
	//	_size = s._size;
	//	_capacity = s._capacity;
	//	return *this;
	//
		if(this != &s){
			string tmp(s._str);
			swap(tmp);	
		}
		return *this;
	}

	//这样也可以
	//string& string::operator=(string tmp){
	//	swap(tmp);
	//	return *this;	
	//}

	void string::insert(size_t pos, const char* str){
		assert(pos <= _size);	
		size_t len = strlen(str);
		if(_size + len >= _capacity){
			size_t newcapacity = _size + len;
			this->reserve(newcapacity);	
		}
		//将所有的元素向后移动len位
		size_t end = _size + len;
		while(end >= pos + len){
			_str[end] = _str[end - len];
			end--;
		}
		//进行拷贝操作
		memcpy(_str + pos, str, len * sizeof(char));
		_size += len;
	}

	void string::insert(size_t pos, const char ch){
		assert(pos <= _size);	
		if(_size == _capacity){
			size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
			this->reserve(newcapacity);	
		}
		//将所有的元素都向后移动一位
		size_t end = _size + 1;
		//这里有一个特殊的情况因为end和pos都是size_t所以要小心当为1时的越界情况
		while(end >= pos + 1){
			_str[end] = _str[end - 1];	
			end--;
		}
		_str[pos] = ch;
		_size++;
	}

	void string::erase(size_t pos, size_t len){	
		assert(pos < _size);
		if(len >= _size - pos){
			_str[pos] = '\0';	
			_size = pos;
		}
		else{
			size_t end = pos + len;
			while(end <= _size){
				_str[pos] = _str[end];
				pos++; end++;
			}		
			_size -= len;
		}
	}
	
	size_t string::find(const char ch, size_t pos){
		assert(pos < _size);
		for(size_t i = pos; i < _size; ++i){
			if(_str[i] == ch) return i;	
		}	
		return npos;
	}

	size_t string::find(const char* str, size_t pos){
		assert(pos < _size);	
		const char* start = strstr(_str, str);	
		if(start == nullptr) return npos;
		else return start - _str;
	}

	void string::swap(string& str){
		//为什么要自己实现：库里面的std::swap对于自定义类型交换的话使用多次拷贝
		//会大大减低效率，所以可以自己实现一个来提升效率
		std::swap(_str, str._str);	
		std::swap(_size, str._size);
		std::swap(_capacity, str._capacity);
	}
	
	void swap(string& x, string& y){
		x.swap(y);	
	}

	string string::substr(size_t pos, size_t len) const{
		assert(pos < _size);
		if(len >= _size - pos){
			string tmp(_str + pos);
			return tmp;	
		}	
		else{
			//这里string是不可以new的，因为new之后没有人对他进行释放
			string sub;
			sub.reserve(len);
			for (size_t i = 0; i < len; i++)
			{
				sub += _str[pos + i];
			}
			return sub;
		}
	}
	//对代码进行复用
	void string::push_back(const char ch){
		this->insert(_size, ch);
	}

	void string::append(const char* str){
		insert(_size, str);	
	}

	void string::reserve(size_t capacity){
		//由于c++中没有类似于realloc的东西，所以开辟更大的空间就要拷贝，赋值，然后删除
		char* tmp = new char[capacity + 1];	
		strcpy(tmp, _str);
		_capacity = capacity;
		delete[] _str;
		_str = tmp;
	}

	string& string::operator+=(const char ch){
		push_back(ch);	
		return *this;
	}

	string& string::operator+=(const char* str){
		append(str);
		return *this;
	}

	const char* string::c_str(){
		return _str;		
	}

	size_t string::size() const{
		return _size;	
	}

	char string::operator[](size_t pos){
		return _str[pos];
	}

	const char string::operator[](size_t pos) const{
		return _str[pos];	
	}
	
	string::iterator string::begin(){
		return _str;
	}

	string::const_iterator string::begin() const { 
		return _str;
	}
	string::iterator string::end(){
		return _str + _size;	
	}
	string::const_iterator string::end() const{
		return _str + _size;	
	}

	void string::clear() {
		_str[0] = '\0';
		_size = 0;	
	}	

	ostream& operator<<(ostream& os, const string& s){
		size_t sz = s.size();
		for(size_t i = 0; i < sz; ++i){
			os << s[i];
		}	
		return os;
	}

	//这里是有一些问题的，就是说每次进行+=然后再扩容或造成很大的效率上的浪费
	istream& operator>>(istream& is,  string& s){
		//首先将显示的内容清空以便下一次显示
		s.clear();
		char buff[128];
		size_t i = 0;
		//这里使用get才可以获取到‘ ’否则普通的scanf 和cin是不会获取空格的
		char ch = is.get();
		while(ch != ' ' && ch != '\n'){
			buff[i++] = ch;
			if(i == 127){
				buff[i] = '\0';
				s += buff;
				i = 0;	
			}
			ch = is.get();	
		}
		return is;
	}
}


