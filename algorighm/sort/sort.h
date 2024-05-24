#pragma once
#include<algorithm>
#include<vector>
#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<ctime>
#include<stack>
#include<utility>
using namespace std;

//插入类排序：希尔排序和插入排序
void InsertSort(vector<int>& arr);
void ShellSort(vector<int>& arr);


//选择类排序有选择排序和堆排序
void SelectSort(vector<int>& arr);


//交换类排序有快排和冒泡排序
void QuickSort(vector<int>& arr, int left, int right);
void QuickSortUnR(vector<int>& arr, int left, int right);
int GetRandomKey(int left, int right);
void QuickSort2(vector<int>& arr, int l, int r);
int GetMuidum(const vector<int>& arr, int left, int right);
//归并类排序
void MergeSort(vector<int>& arr, int n);
void MergeSortUnR(vector<int>& arr, int n);

//还有一种非比较型排序计数排序
