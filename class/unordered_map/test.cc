#include "unordered_map.hpp"


void TestHT1()
{
	spigcoder::unoredred_map<int, int> ht;
	int a[] = {1,13,3,11,5,16,7,6,9,19,29};
	for(auto e : a){
		ht.insert({e,e});
	}
    auto it = ht.begin();
    while(it != ht.end()){
        cout << it->first << ": " << it->second;
        ++it;
        cout << endl;
    }
    cout << endl;
}

int main(){
    TestHT1();
    return 0;
}