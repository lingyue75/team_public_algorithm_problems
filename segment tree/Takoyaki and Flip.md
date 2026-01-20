### Takoyaki and Flip

#### 思路及主要代码
根据题意，一共有三个操作，分别是：  
* 类型 $1$ ：给定整数 $L,R,X$ 。对于 $i=L,L+1,…,R$ ，如果盘子 $i$ 是正面朝上，则在盘子 $i$ 上放置 $X$ 个章鱼烧。  
* 类型 $2$ ：给定整数 $L,R$ 。对于 $i=L,L+1,…,R$ ，如果盘子 $i$ 上至少有一个章鱼烧，则吃掉盘子 $i$ 上的所有章鱼烧。翻转盘子 $i$ （如果盘子是正面朝上，则翻转为反面朝下；否则，翻转为正面朝上）。  
* 类型 $3$ ：给定整数 $L,R$ 。打印盘子 $L$, $L+1,…, R$ 中单个盘子上章鱼烧的最大数量。  

对于类型 $1,3$ 来说，就是区间增加+区间维护最大值，多了一个盘子正面朝上的限制，所以需要 `i64 max, add; bool update` 来维护。  
对于类型 $2$ ，首先是清除盘子上所有的章鱼烧，然后反转范围内所有的盘子。`bool reverse` 来表示是否反转，但只有这个状态会有一些问题。  
一个问题是如果同一个区间遇到了两次反转，`reverse` 就会恢复原样，但反转的同时还需要清空，只有 `reverse` 就会丢失清空信息，所以还需要 `bool check` 来表示是否清空。  
还有对于一段范围的盘子总共有三个状态：全反、有正有反、全正，在反转的时候全反会转成全正，全正转成全反，有正有反的状态反转后是不变的，对于类型 $1$ ，全反时是不放置章鱼烧的，所以需要 `i32 flipped` 来表示三个状态。  

所以总共需要以下的数据：

```C++
struct Info
{
    i64 max, add;
    bool update, reverse, clear;
    i32 flipped;

    Info(): max(0), add(0), update(false), reverse(false), clear(false), flipped(2) {}
};
```

根据上面的分析，这道题需要维护三种懒标记：清空、反转和添加，下面是三个懒更新的实现。

```C++
// 维护增加
void max_lazy(i32 i, i64 v)
{
    if (info[i].flipped != 0) // 全反时不增加
    {
        info[i].max += v;
        info[i].add += v;
        info[i].update = true;
    }
}

// 维护清空
void clear_lazy(i32 i)
{
    info[i].max = 0;
    info[i].add = 0;
    info[i].update = false;
    info[i].clear = true; // 保证在多次反转后始终有清空的操作
}

// 维护反转
void flip_lazy(i32 i)
{
    info[i].reverse = !info[i].reverse; // 如果之前就需要反转，那再转一次就恢复原样了

    // 全正全反的状态是需要改变的
    if (info[i].flipped == 0)
    {
        info[i].flipped = 2;
    }
    else if (info[i].flipped == 2)
    {
        info[i].flipped = 0;
    }
}
```

对于 $up$ 函数，需要去整合两个子节点的最大值与盘子状态，从而保证数据正确性。

```C++
void up(i32 i)
{
    info[i].max = std::max(info[i << 1].max, info[i << 1 | 1].max); // 维护最大值

    // 当左右两边状态不一样时，一定是有正有反
    if (info[i << 1].flipped != info[i << 1 | 1].flipped)
    {
        info[i].flipped = 1;
    }
    else
    {
        info[i].flipped = info[i << 1].flipped;
    }
}
```

对于 $down$ 函数，需要注意三个懒标记的优先级，$clear$ 在前，$reverse$ 在中，$add$ 最后。

```C++
void down(i32 i)
{
    if (info[i].clear)
    {
        clear_lazy(i << 1);
        clear_lazy(i << 1 | 1);

        info[i].clear = false;
    }

    if (info[i].reverse)
    {
        flip_lazy(i << 1);
        flip_lazy(i << 1 | 1);

        info[i].reverse = false;
    }

    if (info[i].update)
    {
        max_lazy(i << 1, info[i].add);
        max_lazy(i << 1 | 1, info[i].add);

        info[i].add = 0;
        info[i].update = false;
    }
}
```

最后，就可以根据这些函数去实现 $add$ ， $reverse$ 和 $query$ 操作了。

#### 主要代码

```C++
class Seg
{
    struct Info
    {
        i64 max, add;
        bool update, reverse, clear;
        i32 flipped;

        Info(): max(0), add(0), update(false), reverse(false), clear(false), flipped(2) {}
    };

    std::vector<Info> info;

    void max_lazy(i32 i, i64 v)
    {
        if (info[i].flipped != 0)
        {
            info[i].max += v;
            info[i].add += v;
            info[i].update = true;
        }
    }

    void clear_lazy(i32 i)
    {
        info[i].max = 0;
        info[i].add = 0;
        info[i].update = false;
        info[i].clear = true;
    }

    void flip_lazy(i32 i)
    {
        info[i].reverse = !info[i].reverse;

        if (info[i].flipped == 0)
        {
            info[i].flipped = 2;
        }
        else if (info[i].flipped == 2)
        {
            info[i].flipped = 0;
        }
    }

    void up(i32 i)
    {
        info[i].max = std::max(info[i << 1].max, info[i << 1 | 1].max);

        if (info[i << 1].flipped != info[i << 1 | 1].flipped)
        {
            info[i].flipped = 1;
        }
        else
        {
            info[i].flipped = info[i << 1].flipped;
        }
    }

    void down(i32 i)
    {
        if (info[i].clear)
        {
            clear_lazy(i << 1);
            clear_lazy(i << 1 | 1);

            info[i].clear = false;
        }

        if (info[i].reverse)
        {
            flip_lazy(i << 1);
            flip_lazy(i << 1 | 1);

            info[i].reverse = false;
        }

        if (info[i].update)
        {
            max_lazy(i << 1, info[i].add);
            max_lazy(i << 1 | 1, info[i].add);

            info[i].add = 0;
            info[i].update = false;
        }
    }
public:
    Seg(i32 size): info((size + 1) << 2) {}

    void add(i32 jobl, i32 jobr, i64 jobv, i32 l, i32 r, i32 i)
    {
        if (l >= jobl && r <= jobr)
        {
            max_lazy(i, jobv);
        }
        else
        {
            i32 mid = l + (r - l) / 2;
            down(i);

            if (jobl <= mid)
            {
                add(jobl, jobr, jobv, l, mid, i << 1);
            }

            if (jobr >= mid + 1)
            {
                add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }

            up(i);
        }
    }

    void reverse(i32 jobl, i32 jobr, i32 l, i32 r, i32 i)
    {
        if (l >= jobl && r <= jobr)
        {
            clear_lazy(i);
            flip_lazy(i);
        }
        else
        {
            i32 mid = l + (r - l) / 2;
            down(i);

            if (jobl <= mid)
            {
                reverse(jobl, jobr, l, mid, i << 1);
            }

            if (jobr >= mid + 1)
            {
                reverse(jobl, jobr, mid + 1, r, i << 1 | 1);
            }

            up(i);
        }
    }

    i64 query(i32 jobl, i32 jobr, i32 l, i32 r, i32 i)
    {
        if (l >= jobl && r <= jobr)
        {
            return info[i].max;
        }

        i32 mid = l + (r - l) / 2;
        down(i);

        i64 ans = lim<i64>::min();
        if (jobl <= mid)
        {
            ans = std::max(ans, query(jobl, jobr, l, mid, i << 1));
        }

        if (jobr >= mid + 1)
        {
            ans = std::max(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
        }

        return ans;
    }
};
```

#### 全部代码

```C++
#include <bits/stdc++.h>
namespace ranges = std::ranges;
namespace views = std::views;

// 基本类型别名
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128;

using u32 = uint32_t;
using u64 = uint64_t;
using u128 = unsigned __int128;

using f32 = float;
using f64 = double;
using f128 = long double;

// 省略std::
using std::string, std::pair, std::tuple, std::queue, std::stack, std::deque;

// 容器类型 - 一维
using vi32 = std::vector<i32>;
using vu32 = std::vector<u32>;
using vi64 = std::vector<i64>;
using vu64 = std::vector<u64>;
using vf32 = std::vector<f32>;
using vf64 = std::vector<f64>;
using vf128 = std::vector<f128>;
using vb = std::vector<bool>;
using vc = std::vector<char>;
using vs = std::vector<string>;

// 容器类型 - 二维
using v2i32 = std::vector<vi32>;
using v2u32 = std::vector<vu32>;
using v2i64 = std::vector<vi64>;
using v2u64 = std::vector<vu64>;
using v2f32 = std::vector<vf32>;
using v2f64 = std::vector<vf64>;
using v2f128 = std::vector<vf128>;
using v2b = std::vector<vb>;
using v2c = std::vector<vc>;
using v2s = std::vector<vs>;

// 数组类型（固定大小）
template<size_t N>
using ai32 = std::array<i32, N>;
template<size_t N>
using ai64 = std::array<i64, N>;
template<size_t N>
using af32 = std::array<f32, N>;
template<size_t N>
using af64 = std::array<f64, N>;

// 映射类型
template<typename T>
using us = std::unordered_set<T>;
template<typename T1, typename T2>
using um = std::unordered_map<T1, T2>;

// 优先队列
template<typename T, typename F>
using pq = std::priority_queue<T, std::vector<T>, F>;

// 最大最小值
template<typename T>
using lim = std::numeric_limits<T>;

class Seg
{
    struct Info
    {
        i64 max, add;
        bool update, reverse, clear;
        i32 flipped;

        Info(): max(0), add(0), update(false), reverse(false), clear(false), flipped(2) {}
    };

    std::vector<Info> info;

    void max_lazy(i32 i, i64 v)
    {
        if (info[i].flipped != 0)
        {
            info[i].max += v;
            info[i].add += v;
            info[i].update = true;
        }
    }

    void clear_lazy(i32 i)
    {
        info[i].max = 0;
        info[i].add = 0;
        info[i].update = false;
        info[i].clear = true;
    }

    void flip_lazy(i32 i)
    {
        info[i].reverse = !info[i].reverse;

        if (info[i].flipped == 0)
        {
            info[i].flipped = 2;
        }
        else if (info[i].flipped == 2)
        {
            info[i].flipped = 0;
        }
    }

    void up(i32 i)
    {
        info[i].max = std::max(info[i << 1].max, info[i << 1 | 1].max);

        if (info[i << 1].flipped != info[i << 1 | 1].flipped)
        {
            info[i].flipped = 1;
        }
        else
        {
            info[i].flipped = info[i << 1].flipped;
        }
    }

    void down(i32 i)
    {
        if (info[i].clear)
        {
            clear_lazy(i << 1);
            clear_lazy(i << 1 | 1);

            info[i].clear = false;
        }

        if (info[i].reverse)
        {
            flip_lazy(i << 1);
            flip_lazy(i << 1 | 1);

            info[i].reverse = false;
        }

        if (info[i].update)
        {
            max_lazy(i << 1, info[i].add);
            max_lazy(i << 1 | 1, info[i].add);

            info[i].add = 0;
            info[i].update = false;
        }
    }
public:
    Seg(i32 size): info((size + 1) << 2) {}

    void add(i32 jobl, i32 jobr, i64 jobv, i32 l, i32 r, i32 i)
    {
        if (l >= jobl && r <= jobr)
        {
            max_lazy(i, jobv);
        }
        else
        {
            i32 mid = l + (r - l) / 2;
            down(i);

            if (jobl <= mid)
            {
                add(jobl, jobr, jobv, l, mid, i << 1);
            }

            if (jobr >= mid + 1)
            {
                add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }

            up(i);
        }
    }

    void reverse(i32 jobl, i32 jobr, i32 l, i32 r, i32 i)
    {
        if (l >= jobl && r <= jobr)
        {
            clear_lazy(i);
            flip_lazy(i);
        }
        else
        {
            i32 mid = l + (r - l) / 2;
            down(i);

            if (jobl <= mid)
            {
                reverse(jobl, jobr, l, mid, i << 1);
            }

            if (jobr >= mid + 1)
            {
                reverse(jobl, jobr, mid + 1, r, i << 1 | 1);
            }

            up(i);
        }
    }

    i64 query(i32 jobl, i32 jobr, i32 l, i32 r, i32 i)
    {
        if (l >= jobl && r <= jobr)
        {
            return info[i].max;
        }

        i32 mid = l + (r - l) / 2;
        down(i);

        i64 ans = lim<i64>::min();
        if (jobl <= mid)
        {
            ans = std::max(ans, query(jobl, jobr, l, mid, i << 1));
        }

        if (jobr >= mid + 1)
        {
            ans = std::max(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
        }

        return ans;
    }
};

void solve()
{
    i32 n, q;
    std::cin >> n >> q;

    Seg tree(n);
    while (q--)
    {
        i32 op, l, r;
        std::cin >> op >> l >> r;

        if (op == 1)
        {
            i64 x;
            std::cin >> x;

            tree.add(l, r, x, 1, n, 1);
        }
        else if (op == 2)
        {
            tree.reverse(l, r, 1, n, 1);
        }
        else
        {
            std::cout << tree.query(l, r, 1, n, 1) << "\n";
        }
    }
}

i32 main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    i32 t = 1;
    while (t--)
    {
        solve();
    }
}
```