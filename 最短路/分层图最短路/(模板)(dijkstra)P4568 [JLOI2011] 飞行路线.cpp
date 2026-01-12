//dj 分层图
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e4 + 5;
const int MAXM = 5e4 * 2 + 5;
const int MAXK = 11;
int n, m, k, s, t;

vector<int> Head(MAXN);
vector<int> Next(MAXM);
vector<int> To(MAXM);
vector<int> Weight(MAXM);
int cnt = 1;

vector<array<int, 2>> heap(MAXN * MAXK);
vector<vector<long long>> dis(MAXN, vector<long long>(MAXK + 1, INT_MAX));
vector<vector<int>> where(MAXN, vector<int>(MAXK + 1, -1));
int hpsz = 0;

void addEdge(int u, int v, int w)
{
    Next[cnt] = Head[u];
    To[cnt] = v;
    Weight[cnt] = w;
    Head[u] = cnt++;
}

void hpInsert(int i)
{
    while(dis[heap[i][0]][heap[i][1]] < dis[heap[(i - 1) / 2][0]][heap[(i - 1) / 2][1]])
    {
        swap(heap[i], heap[(i - 1) / 2]);
        swap(where[heap[i][0]][heap[i][1]], where[heap[(i - 1) / 2][0]][heap[(i - 1) / 2][1]]);
        i = (i - 1) / 2;
    }
}

void heapify(int i)
{
    int l = i * 2 + 1;
    while(l < hpsz)
    {
        int best = l + 1 < hpsz && dis[heap[l + 1][0]][heap[l + 1][1]] < dis[heap[l][0]][heap[l][1]] ? l + 1 : l;
        best = dis[heap[best][0]][heap[best][1]] < dis[heap[i][0]][heap[i][1]] ? best : i;
        if(best == i)
        {
            break;
        }
        swap(heap[best], heap[i]);
        swap(where[heap[i][0]][heap[i][1]], where[heap[best][0]][heap[best][1]]);
        i = best;
        l = i * 2 + 1;
    }
}

void addOrUpdateOrIgnore(int v, int times, long long cost)
{
    if(where[v][times] == -1)
    {
        heap[hpsz][0] = v;
        heap[hpsz][1] = times;
        where[v][times] = hpsz;
        dis[v][times] = cost;
        hpInsert(hpsz++);
    }
    else if(where[v][times] >= 0)
    {
        dis[v][times] = min(dis[v][times], cost);
        hpInsert(where[v][times]);
    }
}

void pop()
{
    swap(heap[0], heap[--hpsz]);
    swap(where[heap[0][0]][heap[0][1]], where[heap[hpsz][0]][heap[hpsz][1]]);
    heapify(0);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m >> k;
    cin >> s >> t;
    for(int i = 0, a, b, c; i < m; i++)
    {
        cin >> a >> b >> c;
        addEdge(a, b, c);
        addEdge(b, a, c);
    }

    addOrUpdateOrIgnore(s, 0, 0);
    while(hpsz != 0)
    {
        int x = heap[0][0];
        int times = heap[0][1];
        int cost = dis[x][times];
        pop();
        if(where[x][times] == -2)
        {
            continue;
        }
        where[x][times] = -2;
        if(x == t)
        {
            cout << cost << "\n";
            break;
        }
        for(int ei = Head[x]; ei != 0; ei = Next[ei])//遍历
        {
            int v = To[ei];
            int w = Weight[ei];
            if(times < k && where[v][times + 1] != -2 && cost < dis[v][times + 1])//免费坐航班
            {
                addOrUpdateOrIgnore(v, times + 1, cost);
            }
            if(where[v][times] != -2 && cost + w < dis[v][times])//不免费
            {
                addOrUpdateOrIgnore(v, times, cost + w);
            }
        }
    }
    return 0;
}