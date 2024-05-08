#include<iostream>
#include<cstring>
using namespace std;

namespace spig {
	class string{
	public:
		//这里不要以为iterator是指针，只是在string这个实现中可以把他实现为指针
		using iterator = char*;
		using const_iterator = const char*;
		string(const char* str = "");	
		~string();
		const char* c_str();
		size_t size();
		char operator[](size_t pos);
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}
