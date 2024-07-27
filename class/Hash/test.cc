#include "Hash.hpp"

void TestHT1()
{
		openlist::Hash<int, int> ht;
	int a[] = {1,13,3,11,5,16,7,6,9,19,29};
	for(auto e : a){
		ht.insert({e,e});
	}
	ht.insert({20,20});
	cout << endl;
	ht.erase(13);
	ht.erase(9);
}

int main(){
    TestHT1();
    return 0;
}