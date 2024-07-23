#include "set.hpp"

void TestSet(){
    set<int> s;
		int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
		for (auto e : a)
		{
			s.insert(e);
		}

		for (auto e : s)
		{
			cout << e << " ";
		}
		cout << endl;

		set<int>::iterator it = s.end();
		while (it != s.begin())
		{
			--it;

			cout << *it << " ";
		}
		cout << endl;

		it = s.begin();
		//*it += 10;
		while (it != s.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;

}

int main(){
    TestSet();
    return 0;
}