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
	cout << tmp.size() << endl;
	for(auto e : tmp){
		cout << e << " ";
	}
	cout << endl;
	tmp.insert(tmp.begin(), 0);
	tmp.insert(tmp.end(), 8);
	tmp.push_back(7);
	tmp.push_back(7);
	tmp.push_back(7);
	tmp.push_back(7);
	tmp.push_back(7);
	tmp.push_back(7);
	tmp.push_back(7);
	for(auto e : tmp){
		cout << e << " ";
	}
	cout << endl;
}

void test_destory(){
	spigcoder::vector<vector<int>> tmp;
	tmp.push_back({1,2,3,4,5,6});
	tmp.push_back({1,2,3,4,5,6});
	tmp.push_back({1,2,3,4,5,6});
	for(auto e : tmp){
		for(auto m : e){
			cout << m << " ";
		}
		cout << endl;
	}
}

int main(){
	test_destory();
	return 0;
}










