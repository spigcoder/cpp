#include "unordered_set.hpp"


void TestHT1()
{
	spigcoder::unoredred_set<int> ht;
	int a[] = {1,13,3,11,5,16,7,6,9,19,29};
	for(auto e : a){
		ht.insert(e);
	}
    auto it = ht.begin();
    while(it != ht.end()){
        cout << *it << " ";
        ++it;
        cout << endl;
    }
    cout << endl;
}

int main(){
    TestHT1();
    return 0;
}