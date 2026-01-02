const int MAXN = 205;
int Move[] = {-1, 0, 1, 0, -1};
bool visited[MAXN][MAXN];
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        //从外围入手， 用小堆维护薄弱边界，然后向中心扩散
        auto comp = [&](auto& a, auto& b){
            return a[2] > b[2];
        };
        priority_queue<array<int, 3>, vector<array<int, 3>>, decltype(comp)> heap(comp);

        int n = heightMap.size();
        int m = heightMap[0].size();

        //把外围加入小堆
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(i == 0 || j == 0 || i == n - 1 || j == m - 1) 
                {
                    heap.push({i, j, heightMap[i][j]});
                    visited[i][j] = true;
                }
                else visited[i][j] = false;
            }
        }

        //弹
        int ans = 0;
        while(heap.size() != 0)
        {
            int x = heap.top()[0];
            int y = heap.top()[1];
            int w = heap.top()[2];
            heap.pop();
            ans += (w - heightMap[x][y]);
            for(int i = 0, nx, ny; i < 4; i++)
            {
                nx = x + Move[i];
                ny = y + Move[i + 1];
                if(nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny])
                {
                    heap.push({nx, ny, max(w, heightMap[nx][ny])});
                    visited[nx][ny] = true;
                }
            }
        }
        return ans;
    }
};