### 小红的树上删边

#### 思路
因为最终每个连通块的大小是偶数，所以在 $n$ 为奇数时必定无解，对于结点 $u$ 以及以 $u$ 为根的子树来说，子树结点的个数如果是偶数，切掉与 $u$ 的边并不会影响 $u$ 所在连通块的奇偶性，删除的边数要尽量多，所以遇到有偶数个结点的子树就切掉为最优策略。  
因为用 $dfs$ 来遍历整棵树，每个结点只会遍历到一次，所以时间复杂度为 $O(n)$ 。

#### 代码

```C++
#include <bits/stdc++.h>

using vi = std::vector<int>;

const int MAXN = 100010;
vi head(MAXN), next(MAXN << 1), to(MAXN << 1); //链式前向星建图 因为是无向图 所以开两倍空间
int n, ans, cnt = 1;

void add_edge(int u, int v)
{
    next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

int dfs(int u, int f)
{
    int cnt = 1;
    for (int ei = head[u], v, num; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f) // 只往下遍历
        {
            num = dfs(v, u); // 子树结点个数
            if (num & 1) // 奇数个不能切
            {
                cnt += num;
            }
            else // 偶数个切掉
            {
                ans++;
            }
        }
    }

    return cnt; // 剩下的结点个数
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n;
    if (n & 1) // 奇数特判
    {
        std::cout << -1 << "\n";
        return 0;
    }

    for (int i = 1, u, v; i < n; i++)
    {
        std::cin >> u >> v;

        // 双向图
        add_edge(u, v);
        add_edge(v, u);
    }

    dfs(1, 0);
    std::cout << ans << "\n";
}
```