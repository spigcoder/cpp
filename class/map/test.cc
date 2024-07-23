#include "map.hpp"

void TestSet(){
    map<int, int> s;
		int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
		for (auto e : a)
		{
			s.insert(make_pair(e,e));
		}

		for (auto e : s)
		{
			cout << e.first << " ";
		}
		cout << endl;
    
    for(auto e : a){
        s[e] = e+1;
        }
		for (auto e : s)
		{
			cout << e.first << ": " << e.second << endl;
		}
		cout << endl;
}

int main(){
    TestSet();
    return 0;
}