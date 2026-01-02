### 华华给月月准备礼物

#### 思路
如果木棍长度为 $x$ ，那么木棍总数就是 $\sum_{i = 1}^{n} arr[i] / x$ ，如果结果大于等于 $k$ ，那么 $x$ 满足条件，否则不满足。对于 $x$ ，如果 $x$ 满足，那么比 $x$ 小的长度必定满足，只需要看比 $x$ 大的数是否满足条件即可，所以可以在 $x$ 的范围上二分，当 $x$ 的值大于给定木棍的最大值 $maxn$ 时，所得到的木棍数量一定为 $0$ ，所以 $x$ 的范围在 $[1, maxn]$ 之间。  
时间复杂度为 $O(nlog(maxn))$ 。

#### 代码

```c++
#include <bits/stdc++.h>

using vi = std::vector<int>;

const int MAXN = 200010;
vi arr(MAXN);
int n, k, maxn;

// 每根木棍长度x，木棍总数能不能满足要求
bool check(int x)
{
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans += arr[i] / x;
    }

    return ans >= k;
}

// 在木棍长度上二分，找出满足要求的最长木棍
int find()
{
    int ans = 0, l = 1, r = maxn, mid;
    while (l <= r)
    {
        mid = l + (r - l) / 2;
        if (check(mid))
        {
            ans = mid;
            l = mid + 1; // 满足条件，在大于x的范围里找
        }
        else
        {
            r = mid - 1; // 不满足，在小于x的范围里找
        }
    }

    return ans;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
        maxn = std::max(maxn, arr[i]); // 二分时的右边界
    }

    std::cout << find() << "\n";
}
```