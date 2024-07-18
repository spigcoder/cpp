#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// class Solution {
// public:

//     int triangleNumber(vector<int>& nums) {
//         sort(nums.begin(), nums.end());
//         int left = 0, right = nums.size() - 1, cur = left + 1, ret = 0;
//         while(left <= right - 2){
//             int target = nums[left], cur = left + 1;
// 			while(right >= left + 2){
//             	while(cur < right){
//             	    if(nums[right] - nums[cur] < target){
//             	        ret += right - cur;
// 						break;
//             	    }
//             	    else{
//             	        cur++;
//             	    }
//             	}
//             	cur = left + 1;
//             	right--;
// 			}
//             left++, right = nums.size() - 1;
//         }
//         return ret;
//     }
// };

// class Solution {
// public:
//     int lengthOfLongestSubstring(string s) {
//         int buff[200] = {0};
//         int max_length = 0, left = 0, right = 0, sz = s.size();
//         while(right < sz){
//             if(buff[s[right]] != 0){
//                 max_length = max(max_length, right - left);
//                 //有重复的数字，将left移到没有重复数字的地方位置
//                 while(left < right){
//                     if(s[left] == s[right]){
//                         buff[left++]--;
//                         break;
//                     }else{
//                         buff[left++]--;
//                     }
//                 }
//             }
//             buff[right++]++;
//         }
//         return max_length;
//     }
// };
class Solution {
public:
    int KZero(const vector<int>& nums){
        int max_length = 0, left = 0, right = 0, num = 0, sz = nums.size();
        while(right < sz){
            if(nums[right] == 0){
                //更新left到第一个非0序列
                while(left < sz && nums[left] == 0){
                    left++;
                }
            }
            right = left;
            if(right > sz) break;
            while(nums[right] == 1) right++;
            max_length = max(max_length, right - left);
        }
        return max_length;
    }

    int longestOnes(vector<int>& nums, int k) {
		if(k == 0) return KZero(nums);
        //这道题，我们可以更改思路，因为翻转k个0并不好算，所以我们可以找连续k个0的个数，找到了就是结果
        int max_length = 0, left = 0, right = 0, num = 0, sz = nums.size();
        while(right < sz){
            if(num >= k){
                //证明[left, right)区间正好有k个0，此时要将left指向最近的0的下一个位置
                while(left < right && nums[left] != 0) { left++; }
                left++, num--;
            }
            while(left < right && nums[right] != 0) { right++; }
            right++, num++;
            while(right < sz && nums[right] != 0) { right++; }
            max_length = max(max_length, right-left);
            cout << max_length << "left is " << left << "right is " << right << endl;
        }
        return max_length;
    }
};

int main(){
	Solution s;
	vector<int> nums = {0,0,1,1,1,0,0};
	cout << s.longestOnes(nums, 0) << endl;
	return 0;
}
