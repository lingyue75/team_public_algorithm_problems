### Takoyaki and Flip

### 1. 题目分析

这道题维护了一个初始长度为 $N$ 的盘子序列，所有盘子初始都是正面朝上，且章鱼烧数量为 $0$。我们需要处理三种区间操作：

* **操作 1（条件增加）**：在区间 $[L, R]$ 中，**仅对正面朝上**的盘子增加 $X$ 个章鱼烧。
* **操作 2（清空并翻转）**：将区间 $[L, R]$ 中的章鱼烧全部吃掉（**数量清零**），并将该区间的盘子**翻转**（正变反，反变正）。
* **操作 3（区间查询）**：查询区间 $[L, R]$ 中的最大章鱼烧数量。

**难点所在**：

1. 操作 1 是带条件的，如果是传统的线段树，遇到“区间内只有部分元素满足条件”时，通常需要一直递归到叶子节点才能修改，这会导致时间复杂度退化。
2. 操作 2 是一个复合操作（清空 + 翻转），它会与操作 1 产生的增加操作产生冲突，如何优雅地处理这几种懒标记的叠加是核心问题。

---

### 2. 核心思路与破局点

要解决“不递归到叶子节点就完成操作 1”的问题，我们需要挖掘题目中隐藏的一个极其重要的**核心性质**：

> **如果一个盘子是反面朝下的，那么它上面的章鱼烧数量一定为 $0$。**

**为什么？**
因为盘子初始都是 $0$。我们只能向正面朝上的盘子加章鱼烧。要把盘子变成反面，唯一的办法是执行操作 2，而操作 2 在翻转的同时，**强制清空了章鱼烧**。

有了这个性质，我们就可以给线段树节点定义一个**盘面状态 (`flipped`)**：

* `0`：区间内所有盘子都是**全反**。
* `2`：区间内所有盘子都是**全正**。
* `1`：区间内盘子**有正有反（混合状态）**。

**如何应用这个性质优化操作 1？**
当我们要给区间加 $X$ 个章鱼烧时：

* 如果区间是**全反 (`0`)**：直接忽略，不加。
* 如果区间是**全正 (`2`)**：区间的最大值直接 $+ X$。
* 如果区间是**混合 (`1`)**：因为反面的盘子一定是 $0$，所以这个区间目前的最大值 `max` 一定是由正面朝上的盘子贡献的（或者全是 $0$）。那么给正面的盘子加 $X$，这个区间的最大值依然会直接变成 `max + X`！**不需要继续向下递归！**

---

### 3. 解决办法 (线段树设计)

基于上述思路，我们的线段树需要维护以下组件：

#### A. 节点信息 (Node Info)

* `max`：当前区间的最大章鱼烧数量。
* `flipped`：当前区间的盘子状态（0全反，1混合，2全正）。

#### B. 懒标记 (Lazy Tags)

* `clear` (布尔值)：是否需要清零。
* `reverse` (布尔值)：是否需要翻转。
* `add` (数值)：累加的章鱼烧数量。
* `update` (布尔值)：配合 `add` 使用，表示是否有增加操作（防止 $X=0$ 时的误判）。

#### C. 标记下放优先级 (PushDown Logic)

当一个节点同时存在多个标记时，下放顺序必须符合操作的物理逻辑：

1. **第一优先级：`clear`**。如果是清空操作，那么之前累计的任何 `add` 都作废了，先清空。
2. **第二优先级：`reverse`**。翻转盘子状态。如果连续翻转两次，就相当于没翻转，可以直接抵消（取反）。
3. **第三优先级：`add`**。最后处理增加操作。只有当子节点的盘子状态不是全反（`flipped != 0`）时，才将 `add` 作用于子节点。

#### D. 信息上传 (PushUp Logic)

* 区间的 `max` 等于左右子节点 `max` 的最大值。
* 区间的 `flipped`：如果左右子节点状态不同，则父节点一定是混合状态（`1`）；如果相同，则父节点继承该状态。

---

### 4. 复杂度分析

* **时间复杂度**：
* **初始化（建树）**：在线段树构造函数中，我们将 `info` 数组的大小初始化为 $(N + 1) \times 4$，这部分的内存分配与初始化的时间复杂度为 $\mathcal{O}(N)$。
* **单次区间操作（增加/翻转/查询）**：线段树的经典结论是，任意一个连续区间 $[L, R]$ 都可以被拆分成最多 $\mathcal{O}(\log N)$ 个线段树的树节点。无论是执行 `add`、`reverse` 还是 `query`，由于懒标记（Lazy Tag）的存在，我们只需要更新被完全覆盖的节点并打上标记，不需要继续向下递归到叶子节点。节点的 `PushDown` 和 `PushUp` 操作内部只有几次基本的算术与逻辑判断，属于 $\mathcal{O}(1)$ 常数操作。因此，单次操作的时间复杂度严格为 $\mathcal{O}(\log N)$。
* **总体时间复杂度**：对于 $Q$ 次操作，总时间复杂度为 $\mathcal{O}(N + Q \log N)$。这在 $N, Q \le 2 \times 10^5$ 级别的数据规模下，可以在几百毫秒内轻松跑过，完全满足竞技编程的时间限制。


* **空间复杂度**：
* 线段树需要开 $4N$ 倍的空间来保证即便是在最坏情况（树满但底层不满）下也不会越界。每个节点 `Info` 内部存储了 2 个 `i64`、3 个 `bool` 和 1 个 `int`，均为常数级别的基础类型，占用空间极小。
* **总体空间复杂度**：$\mathcal{O}(N)$。

---
### 5. 代码实现及详细注释

```cpp
class Seg
{
    struct Info
    {
        i64 max, add;
        bool update, reverse, clear;
        // 0: 全反, 1: 混合, 2: 全正
        // 初始时所有盘子都是正面朝上，所以默认值为 2
        int flipped; 

        Info(): max(0), add(0), update(false), reverse(false), clear(false), flipped(2) {}
    };

    std::vector<Info> info;

    // 核心逻辑 1：处理增加操作的懒标记
    void max_lazy(int i, i64 v)
    {
        // 只有当区间不为“全反”时，增加操作才有效
        // 利用了核心性质：混合状态下的最大值一定来自于正面的盘子
        if (info[i].flipped != 0)
        {
            info[i].max += v;
            info[i].add += v;
            info[i].update = true;
        }
    }

    // 核心逻辑 2：处理清空操作的懒标记
    void clear_lazy(int i)
    {
        info[i].max = 0;
        info[i].add = 0;
        info[i].update = false; // 清空后，之前的增加标记全部作废
        info[i].clear = true;   // 打上清空标记
    }

    // 核心逻辑 3：处理翻转操作的懒标记
    void flip_lazy(int i)
    {
        info[i].reverse = !info[i].reverse; // 两次翻转等于不翻转

        // 维护盘面状态：全反变全正，全正变全反。混合状态(1)翻转后依然是混合状态
        if (info[i].flipped == 0)
        {
            info[i].flipped = 2;
        }
        else if (info[i].flipped == 2)
        {
            info[i].flipped = 0;
        }
    }

    // 向上合并信息 (PushUp)
    void up(int i)
    {
        int ls = i << 1, rs = i << 1 | 1;
        
        // 维护区间最大值
        info[i].max = std::max(info[ls].max, info[rs].max);

        // 维护区间盘面状态
        if (info[ls].flipped != info[rs].flipped)
        {
            info[i].flipped = 1; // 左右状态不同，必定是混合状态
        }
        else
        {
            info[i].flipped = info[ls].flipped; // 左右状态相同，继承该状态
        }
    }

    // 向下传递标记 (PushDown) - 严格遵循优先级规则
    void down(int i)
    {
        int ls = i << 1, rs = i << 1 | 1;

        // 优先级 1: 最先处理清空。因为清空操作是毁灭性的，无视之前的一切增加
        if (info[i].clear)
        {
            clear_lazy(ls);
            clear_lazy(rs);
            info[i].clear = false;
        }

        // 优先级 2: 处理翻转状态
        if (info[i].reverse)
        {
            flip_lazy(ls);
            flip_lazy(rs);
            info[i].reverse = false;
        }

        // 优先级 3: 最后处理增加。在正确的盘面状态下进行累加
        if (info[i].update)
        {
            max_lazy(ls, info[i].add);
            max_lazy(rs, info[i].add);
            info[i].add = 0;
            info[i].update = false;
        }
    }

public:
    Seg(int size): info((size + 1) << 2) {}

    // 对应操作 1：区间增加
    void add(int jobl, int jobr, i64 jobv, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            max_lazy(i, jobv);
            return;
        }
        
        int mid = l + (r - l) / 2;
        down(i); // 必须先下传旧标记，再向子区间递归

        if (jobl <= mid) add(jobl, jobr, jobv, l, mid, i << 1);
        if (jobr > mid)  add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);

        up(i); // 更新当前节点信息
    }

    // 对应操作 2：区间清空并翻转
    void reverse(int jobl, int jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            // 注意顺序：先清空，再翻转
            clear_lazy(i);
            flip_lazy(i);
            return;
        }
        
        int mid = l + (r - l) / 2;
        down(i);

        if (jobl <= mid) reverse(jobl, jobr, l, mid, i << 1);
        if (jobr > mid)  reverse(jobl, jobr, mid + 1, r, i << 1 | 1);

        up(i);
    }

    // 对应操作 3：区间查询最大值
    i64 query(int jobl, int jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            return info[i].max;
        }

        int mid = l + (r - l) / 2;
        down(i);

        i64 ans = lim<i64>::min();
        if (jobl <= mid) ans = std::max(ans, query(jobl, jobr, l, mid, i << 1));
        if (jobr > mid)  ans = std::max(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));

        return ans;
    }
};

void solve()
{
    int n, q;
    std::cin >> n >> q;

    Seg tree(n);
    while (q--)
    {
        int op, l, r;
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
        else if (op == 3)
        {
            std::cout << tree.query(l, r, 1, n, 1) << "\n";
        }
    }
}

```
