#include<iostream>
using namespace std;

class a{
public:
	void print(){
		cout << "print()" << endl;
	}

private:
	int _a;
};

class A{
public:
	void print(){
		cout << _a << endl;
	}

private:
	int _a;
};

int main(){
	a* a1 = nullptr;
	a1->print();
	A* a2 = nullptr;
	a2->print();

	return 0;
}
