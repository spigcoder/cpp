/*这里与买卖股票|||不同的就是可以进行交易的次数有所不同，但是思想还是一致的，只是我们需要更多的变量来对交易进行存储操作*/
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        vector<vector<int>> dp(k, vector<int>(2, 0));
        int n = prices.size(), ret = 0;
        //初始化操作
				//如果相对fanweifor的对象进行更改操作时记得使用引用操作
        for(auto& num : dp){
            num[0] = -prices[0], num[1] = 0;
        }
        auto update = [&](int i){
            dp[0][0] = max(dp[0][0], -prices[i]);
            dp[0][1] = max(dp[0][1], dp[0][0] + prices[i]);
            for(int j = 1; j < k; j++){
                dp[j][0] = max(dp[j][0], dp[j - 1][1] - prices[i]);
                dp[j][1] = max(dp[j][1], dp[j][0] + prices[i]);
            }
        };
        for(int i = 1; i < n; i++){
            update(i);
        }
        for(auto& num : dp){
            ret = max(ret, max(num[0], num[1]));
        }
        return ret;
    }
};


int main(){
	class Solution s;
	vector<int> prices = {2, 4, 1};
	s.maxProfit(2, prices);


	return 0;
}
