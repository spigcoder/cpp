#include<iostream>
#include<assert.h>
using namespace std;

class Date{
/*这里使用ostream作为参数时一定要加引用，因为ostream被禁用了拷贝构造*/
friend ostream& operator<<(ostream& out, const Date& d1);
friend istream& operator>>(istream& in, const Date& d1);


public:
	Date(int year = 1, int month = 1, int day = 1);
	Date(const Date& d);
	Date& operator=(const Date& d);
	~Date();
	//实际上在class中定义的函数会直接声明为内联
	//这里声明为内联是因为这个函数经常被调用，所以在类中定义
	inline int GetMonthDay(int year, int month){
		assert(year > 1 && month < 13 && month > 0);
		//这里使用static可以减少空间的开辟
		static const int Days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		//这里先判断是不是二月会减少很多比较
		if(month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
				return 29;	
		return Days[month];	
	}	

	Date& operator+=(int day);
	Date operator+(int day);
	Date operator-(int day);
	Date& operator-=(int day);
	//++有前置和后置的区别，后置++后面要跟int并且返回值不能用引用，因为返回的是临时对象
	Date& operator++();
	Date operator++(int);
	Date operator--(int);
	Date& operator--();
	bool operator>(const Date& d);
	bool operator<(const Date& d);
	bool operator==(const Date& d);
	bool operator<=(const Date& d);
	bool operator>=(const Date& d);
	bool operator!=(const Date& d);

	//流操作重载，因为操作数与函数的参数顺序要一致，所以我们如果在内部定义成员函数的化
	//this指针一直都占据这第一个参数的位置，所以调用的时候只能是d1 << cout这不符合我们
	//的使用习惯，所以可以使用将其定义为全局函数，但是这样就不可以访问私有变量了，我们
	//有两种解决方法，一种是使用get函数来返回各个值，还有一种就是使用友元函数
	
	//日期减日期
	int operator-(const Date& d);
	//日期加天数
private:
	int _year;
	int _month;
	int _day;
};

//友元函数中的friend只在类的内部使用在外面不用
ostream& operator<<(ostream& out, const Date& d1);
istream& operator>>(istream& in, const Date& d1);












