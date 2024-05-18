#include<string>
#include "vector.h"
#include<vector>

void test_iterator(){
	spigcoder::vector<int> tmp;
	tmp.push_back(1);
	tmp.push_back(2);
	tmp.push_back(3);
	tmp.push_back(4);
	tmp.push_back(5);
	tmp.push_back(6);
	tmp.push_back(7);
	tmp.push_back(9);
	tmp.push_back(11);
	cout << tmp.size() << endl;
	for(auto e : tmp){
		cout << e << " ";
	}
	cout << endl;
	tmp.insert(tmp.begin(), 0);
	for(auto e : tmp){
		cout << e << " ";
	}
	cout << endl;
	cout << "test for erase" << endl;
	spigcoder::vector<int>::iterator it = tmp.begin();
	while(it != tmp.end()){
		if(*it % 2 == 0)
			it = tmp.erase(it);
		else
			it++;
	}
	for(auto e : tmp){
		cout << e << " ";
	}
	cout << endl;
}

void test_destory(){
	spigcoder::vector<string> tmp;
	tmp.push_back("hello");
	tmp.push_back("hello");
	tmp.push_back("hello");
	tmp.push_back("hello");
	tmp.push_back("hello");
	tmp.push_back("hello");
	tmp.push_back("hello");
	for(auto m : tmp){
		cout << m << " ";
	}
	cout << endl;
}

int main(){
	test_iterator();
	return 0;
}










