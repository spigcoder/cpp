#include"sort.h"
#include <iostream>

const int N = 100000;
void SortTest(){
	srand(time(0));
	vector<int> arr1;
	vector<int> arr2;
	for(int i = 0; i < N; i++){
		arr1.emplace_back(rand() + i);
		arr2.emplace_back(rand() + i);
	}


	int begin1 = clock();
	InsertSort(arr1);
	int end1 = clock();

	int begin2 = clock();
	ShellSort(arr2);
	int end2 = clock();

	cout << end1 - begin1 << endl;
	cout << end2 - begin2 << endl;
}

void Print(const vector<int>& arr){
	for(int i = 0; i < arr.size(); i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}

void testsort(){
	vector<int> tmp = {1,3,5,6,8,7,4,9,0,12,32};
//	Print(tmp);
//	InsertSort(tmp);
//	Print(tmp);
//	vector<int> tmp2 = {1,43, 3,65, 4,89 ,6,3,4,654,6,54,23,423,4,345,55,435,3,324,34,4,23424};
//	Print(tmp2);
//	ShellSort(tmp2);
//	Print(tmp2);
	vector<int> tmp3 = {432,4,24,2,423,4,2343,22,423,42,4,534,5,2342,34,4,34,534,1,2,3,2,3,43,24,234,423,434,23,424,23423,5235,42453,21,2435,1,3,5,6,8,7,4,9,0,12,32, 432 ,4 ,324234,234,54323,5,34,23,4234};
	Print(tmp3);
	//int mid = GetMuidum(tmp, 0, tmp.size() - 1);
	//cout << mid << endl;
	MergeSortUnR(tmp3, tmp3.size());
	Print(tmp3);
}

int main(){
	//SortTest();
	testsort();
	srand(time(nullptr));
	return 0;
}
