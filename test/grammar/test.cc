#include "a.hpp"
#include <memory>
#include <string>
#include <thread>
#include <cassert>
#include <cstring>
#include <utility>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <cstdio>
#include <malloc.h>
#include <functional>
using namespace std;

constexpr size_t NUM = 101;
constexpr char TYPE = '#';

int main(){
	char process[NUM];
	string cartoon = "|/-\\";
	size_t sz = cartoon.size();
	//将process的所有元素都置空
	memset(process, '\0', strlen(process));
	for(int i = 0; i < NUM; ++i){
		printf("[%-100s][%d%%][%c]\r",process, i, cartoon[i%sz]);
		process[i] = TYPE;
		fflush(stdout);
		usleep(50000);
	}
	cout << "\r\n";
	return 0;
}