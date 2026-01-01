class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        //01 bfs板子
        
        int n = grid.size();
        int m = grid[0].size();
        int Move[5][2] = {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        //1.
        vector<vector<int>> distances(n, vector<int>(m, INT_MAX));
        deque<array<int, 2>> dq;
        //2.
        dq.push_back({0, 0});
        distances[0][0] = 0;
        //3.
        while(dq.size() != 0)
        {
            int x = dq.front()[0];
            int y = dq.front()[1];
            dq.pop_front();
            //4.
            if(x == n - 1 && y == m - 1)
            {
                return distances[x][y];
            }

            for(int i = 1, nx, ny; i <= 4; i++)
            {
                nx = x + Move[i][0];
                ny = y + Move[i][1];
                int w = (i == grid[x][y]) ? 0 : 1;//是对应方向
                if(nx >= 0 && nx < n && ny >= 0 && ny < m && distances[x][y] + w < distances[nx][ny])
                {
                    distances[nx][ny] = distances[x][y] + w;
                    if(w == 0)
                    {
                        dq.push_front({nx, ny});
                    }
                    else
                    {
                        dq.push_back({nx, ny});
                    }
                }
            }
        }
        return 0;
    }
};