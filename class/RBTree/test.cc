#include "RBTree.hpp"
#include <vector>

void TestRBTree()
{
	const int N = 10000;
	vector<int> v;
	v.reserve(N);
	srand(time(0));

	for (size_t i = 0; i < N; i++)
	{
		v.push_back(i);
		//v.push_back(rand() + i);
	}

	size_t begin2 = clock();
	spigcoder::RBTree<int, int> rbt;
	for (auto e : v)
	{
		rbt.insert(make_pair(e, e));
	}
	size_t end2 = clock();

	cout << "RB Insert:" << end2 - begin2 << endl;

	size_t begin3 = clock();

	cout << "RB Height:" << rbt.Height() << endl;
    cout << rbt.IsBalance();

}

void TestRBTree1(){
    int a[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};

	spigcoder::RBTree<int, int> rbt;
	for (auto e : a)
	{
		rbt.insert(make_pair(e, e));
	}
    rbt.Inorder();
    cout << rbt.IsBalance() << endl;
}

int main(){
    TestRBTree();
    return 0;
}