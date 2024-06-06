#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:

    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int left = 0, right = nums.size() - 1, cur = left + 1, ret = 0;
        while(left <= right - 2){
            int target = nums[left], cur = left + 1;
			while(right >= left + 2){
            	while(cur < right){
            	    if(nums[right] - nums[cur] < target){
            	        ret += right - cur;
						break;
            	    }
            	    else{
            	        cur++;
            	    }
            	}
            	cur = left + 1;
            	right--;
			}
            left++, right = nums.size() - 1;
        }
        return ret;
    }
};

int main(){
	Solution s;
	//vector<int> nums = {2,2,3,4};
	vector<int> nums = {24,3,82,22,35,84,19};
	cout << s.triangleNumber(nums) << endl;
	return 0;
}
