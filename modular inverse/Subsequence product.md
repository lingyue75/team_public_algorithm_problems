### 子数列求积

#### 思路
在长度为 $n$ 的序列上进行静态查询 $[l, r]$ 上的积，可以用一个数组 $mut$ 来记录这个序列的前缀积，然后就可以用 $mut[r] / mut[l - 1]$ ，也就是 $[1, r]$ 的积去除以 $[1, l - 1]$ 的积，得到的值就是 $[l, r]$ 的值了。  
因为算前缀积的可能会爆 $int$ 甚至是 $long long$ ，所以题目要求取模，模数为 $1000000007$ ，在乘法中， $(a * b) \% mod = (a \% mod) * (b \% mod)$ 是正确的，所以在计算前缀积的时候可以直接取模，但对于除法来说， $(a / b) \% mod$ 与 $(a \% mod) / (b \% mod)$ 是不相等的，所以不能直接在两数上取模再相除，而是去计算出每个前缀积的乘法逆元，然后进行乘法取模，乘法逆元的公式是 $inv = x^{mod - 2} \% mod$，然后去计算 $(mut[r] * inv[l - 1]) \% mod$ 就能得出想要的答案了，因为 $mod$ 很大，所以可以用乘法快速幂优化计算。  
时间复杂度为 $O(nlog(len))$ （ $len$ 为模数的二进制长度）。

#### 代码

```C++
#include <bits/stdc++.h>

// 乘法快速幂
long long power(long long x, int n, long long mod)
{
    long long ans = 1;
    while (n > 0)
    {
        if (n & 1)
        {
            ans = (ans * x) % mod;
        }

        x = (x * x) % mod;
        n >>= 1;
    }

    return ans;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    constexpr long long mod = 1000000007;
    int n, q;
    std::cin >> n >> q;

    std::vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
    }

    // 计算前缀积
    std::vector<long long> mut(n + 1, 1);
    for (int i = 1; i <= n; i++)
    {
        mut[i] = (mut[i - 1] * arr[i]) % mod;
    }

    // 计算逆元
    std::vector<long long> inv(n + 1, 1);
    for (int i = 1; i <= n; i++)
    {
        inv[i] = power(mut[i], mod - 2, mod);
    }

    // 离线查询
    for (int i = 1; i <= q; i++)
    {
        int l, r;
        std::cin >> l >> r;

        std::cout << mut[r] * inv[l - 1] % mod << " \n"[i == q];
    }
}
```