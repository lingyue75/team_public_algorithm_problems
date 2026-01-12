const int MAXN = 105;
const int MAXM = 405;//无向图边数要 * 2
const int MAXC = 205;//最大电容量

vector<int> Head(MAXN);
vector<int> Next(MAXM);
vector<int> To(MAXM);
vector<int> Weight(MAXM);
int scnt = 1;

vector<array<int,2>> heap(MAXN * (MAXC + 1));
vector<vector<int>> where(MAXN, vector<int>(MAXC + 1, -1));
vector<vector<int>> dis(MAXN, vector<int>((MAXC + 1), INT_MAX));
int hpsz = 0;

class Solution {
public:
    void Build(int n, int m, int cnt)
    {
        scnt = 1;
        hpsz = 0;
        fill(Head.begin(), Head.begin() + n, 0);
        fill(Weight.begin(), Weight.begin() + m, 0);
        for(int i = 0; i < n; i++)
        {
            fill(where[i].begin(), where[i].begin() + (MAXC + 1), -1);
            fill(dis[i].begin(), dis[i].begin() + (MAXC + 1), INT_MAX);
        }
    }

    void addEdge(int u, int v, int w)
    {
        Next[scnt] = Head[u];
        To[scnt] = v;
        Weight[scnt] = w;
        Head[u] = scnt++;
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
            swap(where[heap[best][0]][heap[best][1]], where[heap[i][0]][heap[i][1]]);
            i = best;
            l = i * 2 + 1;
        }
    }

    void addOrUpdateOrIgnore(int v, int power, int cost)
    {
        if(where[v][power] == -1)//没进堆
        {
            heap[hpsz][0] = v;
            heap[hpsz][1] = power;
            where[v][power] = hpsz;
            dis[v][power] = cost;
            hpInsert(hpsz++);
        }
        else if(where[v][power] >= 0)
        {
            dis[v][power] = min(dis[v][power], cost);
            hpInsert(where[v][power]);
        }
    }

    void pop()
    {
        swap(heap[0], heap[--hpsz]);
        swap(where[heap[0][0]][heap[0][1]], where[heap[hpsz][0]][heap[hpsz][1]]);
        heapify(0);
    }

    int electricCarPlan(vector<vector<int>>& paths, int cnt, int start, int end, vector<int>& charge) {
        //dj分层图最短路 扩点最短路
        int n = charge.size();
        int m = paths.size();

        Build(n, m, cnt);
        //建图
        for(auto& path : paths)
        {
            addEdge(path[0], path[1], path[2]);
            addEdge(path[1], path[0], path[2]);
        }
        //弹
        addOrUpdateOrIgnore(start, 0, 0);
        while(hpsz != 0)
        {
            int x = heap[0][0];
            int power = heap[0][1];
            int cost = dis[x][power];
            pop();
            if(x == end)
            {
                return cost;
            }
            if(where[x][power] == -2)
            {
                continue;
            } 
            where[x][power] = -2;

            if(power + 1 <= cnt && where[x][power + 1] != -2 && cost + charge[x] < dis[x][power + 1])//充电
            {
                addOrUpdateOrIgnore(x, power + 1, cost + charge[x]);
            }

            for(int ei = Head[x]; ei != 0; ei = Next[ei])//去别的地方
            {
                int v = To[ei];
                int w = Weight[ei];
                int restpower = power - w;
                if(restpower >= 0 && where[v][restpower] != -2 && w + cost < dis[v][restpower])
                {
                    addOrUpdateOrIgnore(v, restpower, w + cost);
                }
            }
        }
        return -1;
    }
};