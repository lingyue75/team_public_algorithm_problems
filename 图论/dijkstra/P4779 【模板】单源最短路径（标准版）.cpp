//https://www.luogu.com.cn/problem/P4779
//注意堆的相关函数入参 都在where里
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 1e5 + 5;
const int MAXM = 2e5 + 5;
vector<int> Head(MAXN);
vector<int> Next(MAXM);
vector<int> To(MAXM);
vector<int> Weight(MAXM);
ll cnt = 1;

vector<int> heap(MAXN);
vector<int> where(MAXN, -1);
vector<int> dis(MAXN, INT_MAX);
int hpsz;

int n, m, s;

void addEdge(int u, int v , int w)
{
    Next[cnt] = Head[u];
    To[cnt] = v;
    Weight[cnt] = w;
    Head[u] = cnt++;
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

void addorUpdateorIgnore(int v, int c)
{
    if(where[v] == -1)//v没进过堆
    {
        //进堆
        heap[hpsz] = v;//id在堆的最后
        where[v] = hpsz++;
        dis[v] = c;
        hpInsert(where[v]);
    }
    else if(where[v] >= 0)
    {
        dis[v] = min(dis[v], c);

        hpInsert(where[v]);
    }
}

void heapify(ll i)
{
    int l = i * 2 + 1;
    while(l < hpsz)
    {
        int best = l + 1 < hpsz && dis[heap[l + 1]] < dis[heap[l]] ? l + 1 : l;
        best = dis[heap[best]] < dis[heap[i]] ? best : i;//dis小才更新
        if(best == i)
        {
            break;
        }
        swap(heap[i], heap[best]);
        swap(where[heap[i]], where[heap[best]]);
        i = best;
        l = i * 2 + 1;
    }   
}

int pop()
{
    int ans = heap[0];
    swap(heap[0], heap[--hpsz]);
    swap(where[heap[0]], where[heap[hpsz]]);
    heapify(0);
    where[ans] = -2;//弹完标为-2， 后面不在处理了
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s;
    for(int i = 0; i < m; i++)//建图
    {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }

    //弹
    addorUpdateorIgnore(s, 0);
    while(hpsz != 0)
    {
        int cur = pop();
        //遍历所有边
        for(int ei = Head[cur]; ei != 0; ei = Next[ei])
        {
            int v = To[ei];
            int w = Weight[ei];
            addorUpdateorIgnore(v, dis[cur] + w);
        }
    } 

    for(int i = 1; i <= n; i++)
    {
        cout << dis[i] << " ";
    }
    cout << "\n";
    return 0;
}