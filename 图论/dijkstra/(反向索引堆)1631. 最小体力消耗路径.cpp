//where[x][y]是点在堆的什么下标， heap[i][0] : x , heap[i][1] : y
const int MAXN = 105;
const int MAXM = 105;
vector<array<int, 2>> heap(MAXN * MAXM);
vector<vector<int>> dis(MAXN, vector<int>(MAXM, INT_MAX));
vector<vector<int>> where(MAXN, vector<int>(MAXM, -1));
int hpsz = 0;

class Solution {
public:
    void Build(int n, int m)
    {
        hpsz = 0;
        for(int i = 0; i < n; i++)
        {
            fill(dis[i].begin(), dis[i].begin() + m, INT_MAX);
            fill(where[i].begin(), where[i].begin() + m, -1);
        }
    }

    void hpInsert(int i)
    {
        while(dis[heap[i][0]][heap[i][1]] < dis[heap[(i - 1) / 2][0]][heap[(i - 1) / 2][1]])//距离小才换
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
            best = dis[heap[best][0]][heap[best][1]] < dis[heap[i][0]][heap[i][1]] ? best : i;//距离小才换
            if(best == i)
            {
                break;
            }
            swap(heap[best],heap[i]);
            swap(where[heap[best][0]][heap[best][1]], where[heap[i][0]][heap[i][1]]);
            i = best;
            l = i * 2 + 1;
        }
    }

    void pop()
    {
        swap(heap[0], heap[--hpsz]);
        swap(where[heap[0][0]][heap[0][1]], where[heap[hpsz][0]][heap[hpsz][1]]);
        heapify(0);
    }

    void addOrUpdateOrIgnore(int x, int y, int c)
    {
        if(where[x][y] == -1)//没进过堆
        {
            heap[hpsz][0] = x;
            heap[hpsz][1] = y;
            where[x][y] = hpsz++;
            dis[x][y] = c;
            hpInsert(where[x][y]);
        }
        else if(where[x][y] >= 0)//Update
        {
            dis[x][y] = min(dis[x][y], c);
            hpInsert(where[x][y]);
        }
    }

    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();
        int Move[] = {-1, 0, 1, 0, -1};
        Build(n, m);

        addOrUpdateOrIgnore(0, 0, 0);
        while(hpsz != 0)
        {
            int x = heap[0][0];
            int y = heap[0][1];
            pop();
            if(where[x][y] == -2)
            {
                continue;
            }
            if(x == n - 1 && y == m - 1)
            {
                return dis[x][y];
            }
            where[x][y] = -2;
            for(int i = 0, nx, ny; i < 4; i++)
            {
                nx = x + Move[i];
                ny = y + Move[i + 1];
                if(nx >= 0 && nx < n && ny >= 0 && ny < m && where[nx][ny] != -2)
                {
                    int nc = max(abs(heights[nx][ny] - heights[x][y]), dis[x][y]);
                    addOrUpdateOrIgnore(nx, ny, nc);
                }
            }
        }
        return -1;
    }
};