#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
	vector<int> nums = {1,2,2,3,4,5,5,5,5,6};
	auto last = unique(nums.begin(), nums.end());
	nums.erase(last, nums.end());
	for(auto num : nums){
		cout << num << " ";
	}	
	cout << endl;
	cout << sizeof(int&) << endl;
	cout << sizeof(double&) << endl;

	return 0;
}
