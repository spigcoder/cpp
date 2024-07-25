#include <stack>
#include <vector>
#include <cstdio>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;


  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  
  };


class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> t_map, s_map;
        for(auto e : t) t_map[e]++;
        int num = t_map.size(), left = 0, sz = s.size(), count = 0, right = 0;
        string ret = "";
        while(right < sz){
            if(t_map.count(s[right])) s_map[s[right]]++;
            if(t_map.count(s[right]) && s_map[s[right]] == t_map[s[right]]) count++;
            if(count == num){
                //比较，出窗口
                if(ret == "") ret = s.substr(left, right-left+1);
                else{
                    if(right-left+1 < ret.size()){
                        ret = s.substr(left, right-left+1);
                    }
                }
                if(t_map.count(s[left])){
                    s_map[s[left]]--;
                    //如果s_map中这个元素不满足t_map对这个元素的要求再进行--
                    if(s_map[s[left]] < t_map[s[left]]) count--;
                }
                left++;
                //将left移动带下一个t中含有的字符的位置
                while(left < sz && !t_map.count(s[left])){
                    left++;
                }
            }
            right++;
        }
        return ret;
    }
};
int main(){
    string s = "lingmindraboofooowingdingbarrwingmonkeypoundcake";
    vector<string> test = {"fooo","barr","wing","ding","wing"};
    string ret = Solution().minWindow("a", "a");
    cout << ret << endl;
    return 0;
}
