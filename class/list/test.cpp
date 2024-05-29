#include"list.h"
#include<iostream>

template<typename T>
void display(spigcoder::list<T> li){
	typename spigcoder::list<T>::iterator it = li.begin();
	//li.display();
	while(it != li.end()){
		std::cout << *it << " ";	
		++it;
	}
	std::cout << std::endl;
}

void test_display_insert(){
	spigcoder::list<int> list1;
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);
	list1.push_back(4);
	list1.push_back(5);
	display(list1);
	list1.push_front(-2);
	list1.push_front(-1);
	list1.push_front(0);
	display(list1);
	list1.pop_front();
	list1.pop_front();
	list1.pop_front();
	display(list1);
	list1.pop_back();
	list1.pop_back();
	list1.pop_back();
	display(list1);
}

void test_assign(){
	spigcoder::list<int> list1;
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);
	list1.push_back(4);
	list1.push_back(5);
	display(list1);
	spigcoder::list<int> list2(list1);
	display(list2);
	spigcoder::list<int> list3;
	list3.push_back(10);
	list3.push_back(20);
	list3.push_back(30);
	list3.push_back(40);
	display(list3);	
	list2 = list3;
	display(list2);
}

int main(){
	//test_display_insert();	
	test_assign();
	return 0;
}
