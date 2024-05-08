#include"string.h"

void test1(){
	spig::string str1("Hello spig");
	cout << str1.c_str() << endl;
	cout << str1.size() << endl;
	for(auto ch : str1){
		cout << ch << " ";
	}
	cout << endl;
	for(auto ch : str1){
		cout << ch + 1 << " ";
	}
	cout << endl;
	const spig::string str2("Hello, spig");
	for(auto ch : str2){
		cout << ch << " ";
	}
	cout << endl;
	for(auto& ch : str2){
		cout << ch + 1 << " ";
	}
	cout << endl;
	for(auto ch : str2){
		cout << ch << " ";
	}
	cout << endl;
}

void test2(){
	const spig::string str1("Hello pig");
	spig::string::const_iterator it = str1.begin();
	while(it != str1.end()){
		cout << *it << " ";
		it++;
	}
	cout << endl;
//	while(it != str1.end()){
//		cout << (*it)++ << " ";
//		it++;
//	}

}

int main(){
	test1();
	return 0;
}
