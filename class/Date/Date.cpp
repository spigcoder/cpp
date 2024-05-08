#include"Date.h"
#include <ostream>

Date::Date(int year, int month, int day){
	_year = year;
	_month = month;
	_day = day;
}

Date::Date(const Date& d){
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

//这里只有在出了作用域返回值不销毁的情况下才可以使用引用返回，目的是减少拷贝
Date& Date::operator=(const Date& d){
	_year = d._year;
	_month = d._month;
	_day = d._day;
	return *this;
}

Date::~Date(){
	_year = 0;
	_month = 0;
	_day = 0;	
}


Date& Date::operator+=(int day){
	if(day < 0)
		*this -= -day;
	_day += day;
	while(_day > GetMonthDay(_year,_month)){
		_day -= GetMonthDay(_year, _month);
		++_month;
		if(_month == 13){
			_month = 1;
			++_year;
		}	
	}
	return *this;
}

Date Date::operator+(int day){
	Date tmp = *this;
	tmp += day;
	return tmp;
}

Date& Date::operator-=(int day){
	if(day < 0)
		*this += -day;	

	_day -= day;
	while(_day <= 0){
		--_month;
		if(_month == 0){
			_month = 12;
			--_year;
		}
		_day += GetMonthDay(_year, _month);	
	}
	return *this;
}

Date Date::operator-(int day){
	Date tmp = *this;
	tmp -= day;
	return tmp;

}

ostream& operator<<(ostream& out, const Date& d1){
	out << d1._year << "年" << d1._month << "月" << d1._day << "日";
	return out;
}
//没有参数的是前置加加，返回的是加加以后的值，因为直接对this指针进行++操作，所以可以
//使用引用返回（当返回对象出了当前函数的作用域还存在时可以使用引用返回）
Date& Date::operator++(){
	*this += 1;
	return *this;
}

Date Date::operator++(int){
	Date tmp = *this;
	*this += 1;
	return tmp;
}

Date& Date::operator--(){
	*this -= 1;
	return *this;
}

Date Date:: operator--(int){
	Date tmp = *this;
	*this -= 1;
	return tmp;
}

//比较操作
bool Date::operator>(const Date& d){
	if (this->_year < d._year)
		return false;
	else if(this->_year == d._year){
		if(this->_month < d._month){
			return false;
		}
		else if(this->_month == d._month){
			if(this->_day <= d._day)
				return false;
		}
		else 
			return true;
	}
	else
		return true;
	return true;
}

bool Date::operator==(const Date& d){
	return this->_year == d._year 
		&& this->_month == d._month 
		&& this->_day == d._day;
}

//这里就是一个代码复用的思想，使用曾经写过的代码来进行复用操作

bool Date::operator<=(const Date& d){
	return !(*this > d);
}

bool Date::operator>=(const Date& d){
	return (*this > d || *this == d);
}


bool Date::operator<(const Date& d){
	return !(*this >= d); 
}


bool Date::operator!=(const Date &d){
	return !(*this == d);
}

int Date::operator-(const Date& d){
	int tag = 1, count = 0;
	Date max = *this;
	Date min = d;
	if(max < min){
		max = d;
		min = *this;
		//因为操作数的顺序与参数的顺序是相同的，所以如果d比this大的化结果就是一个负值
		tag = -1;
	}
	while(min != max){
		min += 1;
		count++;
	}
	return tag * count;
}
















