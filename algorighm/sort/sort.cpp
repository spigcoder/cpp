#include "sort.h"

void swap(int& a, int& b){
	int tmp = a;
	a = b;
	b = tmp;
}

//插入排序是一种相对稳定的排序它是将一个数向前插入
//直到遇到比它小的数就停止插入，这样也导致了它有较好的适应性
void InsertSort(vector<int>& arr){
	for(int i = 1; i < arr.size(); i++){
		//从这个位置开始向前进行比较
		for(int j = i; j > 0 ; j--){
			if(arr[j] < arr[j - 1]){
				swap(arr[j], arr[j - 1]);
			}
			else break;
		}
	}
}

//希尔排序是在插入排序的基础上进行修复
//因为插入排序对于近似有序的数的效率比较高，所以我们可以让他近似有序
//这就是希尔排序，先对距离较大的数进行交换，这样可以得到一个近似有序的数组
//最后再进行插入排序（插入排序就是gap = 1的希尔排序）
void ShellSort(vector<int>& arr){
	int n = arr.size(), k = 0;
	//找到一个合适的向前调整的值
	while(k < n) k = k * 3 + 1;
	while(k >= 1){
		for(int i = k; i < n; i++){
			for(int j = i; j >= k; j -= k){
				if(arr[j] < arr[j - k]) swap(arr[j], arr[j - k]);
				else break;
			}
		}
		k  = (k - 1) / 3 ;
	}
}

//快速排序是一种交换类排序，找到一个key值然后将key值左边为小于key的
//右边为大于key的

int GetRandomKey(int left, int right){
	int n = rand() % (right - left + 1);

	return n + left;
}

//三数取中法也是一个相对较为优化的方法，目的是为了在每次递归调用左右区间时
//可以尽可能的二分调用，这样可以提高效率并且防止最坏的情况发生（顺序或者逆序）
//但是这里要理解的是三数取中取得是数而不是下标
int GetMuidum(const vector<int>& arr, int left, int right){
	int mid = left + (right - left) / 2;
	if(arr[mid] < arr[left]){
		if(arr[mid] > arr[right])
			return arr[mid];
		else if(arr[left] < arr[right])
			return arr[left];
		else 
			return arr[right];
	}else{
		if(arr[mid] < arr[right])
			return arr[mid];
		else if(arr[right] > arr[left])
			return arr[right];
		else 
			return arr[left];
	}
}

void QuickSort(vector<int>& arr, int left, int right){
	int key = arr[left];
	if(left >= right) return;
	int begin = left, end = right;
	//这里要注意终止的条件，当left与right相等是就是中止的时候
	while(left < right){
		//right是要寻找比key小的值
		while(left < right && arr[right] >= key)
			right--;
		//left寻找比key大的值
		while(left < right && arr[left] <= key)
			left++;
		swap(arr[left], arr[right]);
	}
	//begin是原来第一个位置，也就是key的值
	swap(arr[left], arr[begin]);
	for(auto num : arr) cout << num << " ";
	cout << endl;
	QuickSort(arr, begin, left - 1);
	QuickSort(arr, right + 1, end);
}

//使用左右区间法来进行快排的实现
void QuickSort2(vector<int>& arr, int l, int r){
	if(l >= r) return;
	//随机数法取key
	//int key = arr[GetRandomKey(l, r)];
	int key = GetMuidum(arr, l, r);
	//left 和 right 分别表示的是
	//左区间的最后一个值和右区间的第一个值
	//l和r则是要进行排序的区间的第一个和最后一个值
	int left = l - 1, right = r + 1, cur = l;
	while(cur < right){
		if(arr[cur] == key) cur++;
		else if(arr[cur] < key)
			swap(arr[cur++], arr[++left]);
		else 
			//这里cur不能++因为交换过来的元素还没有进行判断比较
			swap(arr[cur], arr[--right]);
	}	
	//递归左右子区间
	QuickSort2(arr, 0, left);
	QuickSort2(arr, right, r);
}

//这里是使用非递归来进行快速排序的实现，非递归实现一些东西
//就要借助栈完成因为栈也是先进后出的与递归类似
//stack中存储的是下一次要进行操作的区间
void QuickSortUnR(vector<int> &arr, int l, int r){
	stack<pair<int, int>> st;
	st.push({l, r});
	while(!st.empty()){
		auto[le, ri] = st.top();
		st.pop();
		int left = le - 1, right = ri + 1, cur = le;
		int key = arr[GetRandomKey(le, ri)];
		while(cur < right){
			if(arr[cur] == key) cur++;
			else if(arr[cur] < key) swap(arr[cur++], arr[++left]);
			else swap(arr[cur], arr[--right]);
		}
		//递归左右子区间
		if(left > 0) st.push({0, left});
		if(right < ri) st.push({right, ri});
	}

}

void _MergeSort(vector<int>& arr, int begin, int end, vector<int>& tmp){
	if(begin >= end) return;
	int mid = begin + (end - begin) / 2;
	_MergeSort(arr, begin, mid, tmp);
	_MergeSort(arr, mid + 1, end, tmp);
	int begin1 = begin, end1 = mid;
	int begin2 = mid + 1, end2 = end;
	//这里的i可以从0开始也可以从begin1开始，看个人习惯
	int i = 0;
	//进行归并排序
	while(begin1 <= end1 && begin2 <= end2){
		//这个如果是<=那么就是稳定的排序，否则是不稳定的
		if(arr[begin1] <= arr[begin2]) tmp[i++] = arr[begin1++];
		else tmp[i++] = arr[begin2++];
	}
	//将没有排序完的惊醒排序
	while(begin1 <= end1) tmp[i++] = arr[begin1++];
	while(begin2 <= end2) tmp[i++] = arr[begin2++];
	//将排序后的数组覆盖到原数组中去，但这里要注意的是i的初始值
	//因为更改的是原数组中begin处的位置，所以如果i的初值是0的话要注意更改
	for(int j = 0; j < i; j++){
		arr[j + begin] = tmp[j];
	}
}

//merge就是假设左区间和右区间都是有序的，然后进行有序数组的合并
void MergeSort(vector<int>& arr, int n){
	vector<int> tmp(n, 0);
	_MergeSort(arr, 0, n - 1, tmp);
}

//为什么归并排序的非递归不用栈来实现
//因为merge实际上是一种后续遍历是先找到叶子节点再向上回溯而不是
//像快排那样先对原始队列进行操作再去递归子问题，如果用栈的话回来
//会存不到要进行合并的节点会相对较为麻烦，我们的解决方法就是直接循环
//以最小子问题来进行解决
void MergeSortUnR(vector<int> &arr, int n){
	int gap = 1;
	vector<int> tmp(n , 0);
	while(gap < n){
		//因为是两个队列两个队列进行排序的所以乘2
		for(int j = 0; j < n; j += gap * 2){
			int begin1 = j, end1 = j + gap - 1;
			int begin2 = end1 + 1, end2 = begin2 + gap - 1;
			//这是为了防止越界情况发生
			if(end1 >= n || begin2 >= n) break;
			if(end2 >= n) end2 = n - 1;
			int i = 0;
			while(begin1 <= end1 && begin2 <= end2){
				if(arr[begin1] <= arr[begin2]) tmp[i++] = arr[begin1++];		
				else tmp[i++] = arr[begin2++];
			}
			while(begin1 <= end1) tmp[i++] = arr[begin1++];
			while(begin2 <= end2) tmp[i++] = arr[begin2++];
			//惊醒数组的拷贝
			for(int m = 0; m < i; m++){
				arr[m + j] = tmp[m];
			}
		}
		gap *= 2;
	}
}
