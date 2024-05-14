#include"string.h"
#include <ostream>

void test1(){
	std::string str1("Hello spig");
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
	for(auto ch : str2){
		cout << ++ch  << " ";
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

void test_insert(){
	spig::string s1("Hello World ");
	cout << s1 << endl;
	cout << "test for insert" << endl;
	s1.insert(0, "insert in 0");
	cout << s1 << endl;
	s1.insert(s1.size(), "insert in end");
	cout << s1 << endl << endl;
	spig::string s2("Hello World ");
	s2.append("test for append");
	cout << s2 << endl << endl;
	spig::string s3("Hello World ");
	s3 += "This is test for +=";
	cout << s3 << endl << endl;
	spig::string s4("Hello World ");
	cout << "This is test for erase";
	s4.erase(1);
	cout << s4 << endl << endl;
}

void test_find(){
	cout << "test for find" << endl;
	spig::string s4("Hello World ");
	size_t pos = s4.find("World");
	s4.insert(pos, "this is the position for World ");
	cout << s4 << endl << endl;
	spig::string s5("Hello World ");
	spig::string s6 = s5.substr(5, 6);	
	cout << s6 << endl << endl;
}

int main(){
	test1();
	test_insert();
	test_find();
	return 0;
}


































