#include<iostream>
#include<cstring>
#include<assert.h>
#include <ostream>
#include<utility>
using namespace std;

namespace spig {
	class string{
	public:
		//这里不要以为iterator是指针，只是在string这个实现中可以把他实现为指针
		using iterator = char*;
		using const_iterator = const char*;
		string(const char* str = "");	
		~string();
		string(const string& str);

		void reserve(size_t sz);
		const char* c_str();
		size_t size() const;

		string& operator+=(const char ch);
		string& operator+=(const char* str);
		string& operator=(const string& s);
		char operator[](size_t pos);
		const char operator[](size_t pos) const;

		void append(const char* str);
		void push_back(const char ch);
		void insert(size_t pos, const char ch);
		void insert(size_t pos, const char* str);
		void erase(size_t pos, size_t len = npos);
		size_t find(const char ch, size_t pos = 0);
		size_t find(const char* str, size_t pos = 0);
		void swap(string& str);
		string substr(size_t pos = 0, size_t len = npos) const;
		void clear();	

		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
	private:
		const static size_t npos;
		char* _str;
		size_t _size;
		size_t _capacity;
	};
	void swap(string& x, string& y);
	ostream& operator<<(ostream& os, const string& str);
	istream& operator>>(istream& is, const string& str);
}
