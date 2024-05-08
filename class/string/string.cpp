#include"string.h"

//相同的命名空间会在链接阶段进行合并
namespace spig{
	//缺省参数如果定义与声明分离，在声明处给缺省参数
	string::string(const char* str)
	:_size(strlen(str))
	{
		_str = new char[_size + 1];	
		strcpy(_str, str);
		_capacity = _size;
	}
	
	const char* string::c_str(){
		return _str;		
	}

	string::~string(){
		delete [] _str;
		_str = nullptr;
		_size = _capacity = 0;
	}

	size_t string::size(){
		return _size;	
	}

	char string::operator[](size_t pos){
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
}

