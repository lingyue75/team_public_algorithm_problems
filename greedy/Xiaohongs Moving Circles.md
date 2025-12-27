### 小红的圆移动

#### 思路
对于不包含原点的圆没有必要移动，所以只记录所有包含原点的圆，数量为 $num$ 个，一次操作的代价为该圆面积与移动距离，面积是固定的，因为是最小代价，所以移动距离要最小，为 $r - dis$ （ $dis$ 为圆心到原点距离），将所有的代价收集起来，从小到大排序，因为不要超过 $k$ 个，所以从头选取 $max(num - k, 0)$ 个即可。
时间复杂度为 $O(nlogn)$ 。

#### 代码

```C++
#include <bits/stdc++.h>

using vd = std::vector<double>;

const int MAXN = 100010;
const double PI = std::acos(-1); // arccos(-1) = PI
vd arr(MAXN);
int n, k, num;
double ans;

// 点到圆心距离
double dist(int x, int y)
{
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

int main()
{
    // 输入输出用scanf, prinf最方便，cin需要注意精度问题，默认是6位有效数字
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> k;
    for (int i = 1, x, y, r; i <= n; i++)
    {
        std::cin >> x >> y >> r;

        double dis = dist(x, y);
        if (dis < r)
        {
            arr[num++] = (std::pow(r, 2) * PI) * (r - dis);
        }
    }

    std::sort(arr.begin(), arr.begin() + num);

    for (int i = 0; i < num - k; i++)
    {
        ans += arr[i];
    }

    /*
    std::fixed: 让浮点数输出为定点表示法，显示固定的小数位数。
    std::setprecision(16): 控制小数点后的位数。
    如果使用了 std::fixed，则设置的小数位数是精确到小数点后的位数。
    如果没有使用 std::fixed，则 setprecision 会影响总的有效位数
    （包括整数部分和小数部分）。
    */
    std::cout << std::fixed << std::setprecision(16) << ans << "\n";
}
```