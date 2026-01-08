// 测试链接 : https://leetcode.cn/problems/network-delay-time
const int MAXN = 105;
const int MAXM = 6005;
vector<int> Head(MAXN);
vector<int> Next(MAXM);
vector<int> To(MAXM);
vector<int> Weight(MAXM);
int cnt = 1;

vector<int> heap(MAXN);
vector<int> where(MAXN);
vector<int> dis(MAXN);
int hpsz = 0;

class Solution {
public:
    void Build(int n)
    {
        cnt = 1;
        hpsz = 0;
        fill(Head.begin() + 1, Head.begin() + n + 1, 0);
        fill(dis.begin() + 1, dis.begin() + n + 1, INT_MAX);
        fill(where.begin() + 1, where.begin() + n + 1, -1);
    }

    void addEdge(int u, int v, int w)
    {
        Next[cnt] = Head[u];
        Head[u] = cnt;
        To[cnt] = v;
        Weight[cnt++] = w;
    }

    void hpInsert(int i)
    {
        while(dis[heap[i]] < dis[heap[(i - 1) / 2]])
        {
            swap(heap[i], heap[(i - 1) / 2]);
            swap(where[heap[i]], where[heap[(i - 1) / 2]]);
            i = (i - 1) / 2;
        }
    }

    void addorUpdateorIngnore(int v, int c)
    {
        if(where[v] == -1)//没进过hp
        {
            //进hp where dis更新 
            heap[hpsz] = v;
            where[v] = hpsz++;
            dis[v] = c;//
            hpInsert(where[v]);
        }
        else if(where[v] >= 0)
        {
            dis[v] = min(dis[v], c);
            hpInsert(where[v]);//
        }
    }

    int pop()
    {
        int ans = heap[0];
        swap(heap[0], heap[--hpsz]);
        swap(where[heap[0]], where[heap[hpsz]]);
        heapify(0);//pop完向下调整
        where[ans] = -2;//弹过就 where变成 -2
        return ans;
    }

    void heapify(int i)//
    {
        int l = i * 2 + 1;
        while(l < hpsz)
        {
            int best = l + 1 < hpsz && dis[heap[l + 1]] < dis[heap[l]] ? l + 1 : l;
            best = dis[heap[best]] < dis[heap[i]] ? best : i;//一定是dis小的在上面    leetcode数据也太松了 这个没写居然能过
            if(best == i)
            {
                return ;
            }
            swap(heap[i], heap[best]);
            swap(where[heap[i]], where[heap[best]]);
            i = best;
            l = i * 2 + 1;
        }
    }

    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        //单源最短路求 最大值 无负权 dj
        //反向索引堆 加 链式前向星
        Build(n);
        int m = times.size();
        //建图
        for(int i = 0; i < m; i++)
        {
            addEdge(times[i][0], times[i][1], times[i][2]);
        }
    
        //弹
        addorUpdateorIngnore(k, 0);
        while(hpsz != 0)
        {
            int cur = pop();
            //弹完就开始遍历边
            for(int ei = Head[cur]; ei != 0; ei = Next[ei])
            {
                int v = To[ei];
                int w = Weight[ei];
                addorUpdateorIngnore(v, dis[cur] + w);//
            }
        }
        
        int mx = *max_element(dis.begin() + 1, dis.begin() + n + 1);
        return mx == INT_MAX ? -1 : mx;
    }
};