//https://leetcode.cn/problems/closest-subsequence-sum/
using ll = long long;
const ll MAXN = 45;
const ll MAXM = 1 << 20 + 5;
ll lsum[MAXM]{};
ll rsum[MAXM]{};

class Solution {
public:
    ll f(ll i, ll e, ll sum, ll* ans, ll j, vector<int>& nums)
    {
        if(i == e)
        {
            ans[j++] = sum;
        }
        else
        {
            //加
            j = f(i + 1, e, sum + nums[i], ans, j, nums);
            //不加
            j = f(i + 1, e, sum, ans, j, nums);
        }
        return j;
    }
    int minAbsDifference(vector<int>& nums, int goal) {
        //通过数据量猜解法
        //双向广搜
        int n = nums.size();
        ll lsize = f(0, n >> 1, 0, lsum, 0, nums);
        ll rsize = f(n >> 1, n, 0, rsum, 0, nums);
        sort(lsum, lsum + lsize);
        sort(rsum, rsum + rsize);
        //双指针
        ll ans = INT_MAX;
        for(int i = 0, j = rsize - 1; i < lsize; i++)
        {
            while(j > 0 && abs(goal - lsum[i] - rsum[j - 1]) <= abs(goal - lsum[i] - rsum[j]))//差值小才更新
            {
                j--;
            }
            ans = min(ans, abs(goal - lsum[i] - rsum[j]));
        }
        return ans;
    }
};