#include <stack>
#include <vector>
#include <cstdio>
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
    vector<int> findSubstring(string s, vector<string>& words) {
        unordered_map<string, int> word_map;
        vector<int> ret;
        for(const auto& e : words) word_map[e]++;
        int total_num = words.size(), length = words[0].size(), sz = s.size();
        for(int i = 0; i < length; i++){
            unordered_map<string, int> s_map;
            for(int left = i, right = i; right+length <= sz; right += length){
                string sub_str = s.substr(right, length);
                s_map[sub_str]++;

                while(s_map[sub_str] > word_map[sub_str]){
                    string sub_str1 = s.substr(left,length);
                    s_map[sub_str1]--;
                    left += length;
                }
                if((right-left+length)/length == total_num) ret.push_back(left);
            }
        }
        return ret;
    }
};
int main(){
    string s = "lingmindraboofooowingdingbarrwingmonkeypoundcake";
    vector<string> test = {"fooo","barr","wing","ding","wing"};
    Solution().findSubstring(s, test);
    return 0;
}
