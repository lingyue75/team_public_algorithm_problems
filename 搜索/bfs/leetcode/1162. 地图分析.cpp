class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        //bfs
        const int MAXN = 101;
        const int MAXM = 101;
        vector<array<int, 2>> q(MAXN * MAXM);
        vector<int> move = {-1, 0, 1, 0, -1};//代替上下左右
        bool visited[MAXN][MAXM] = {false};
        int l = 0, r = 0;
        int n = grid.size(), m = grid[0].size();
        int sea = 0;
        for(int i = 0; i < n; i++)//遍历标记bfs的源
        {
            for(int j = 0; j < m; j++)
            {
                if(grid[i][j] == 1)
                {
                    q[r][0] = i;
                    q[r++][1] = j;
                    visited[i][j] = true;
                }
                else
                {
                    visited[i][j] = false;
                    sea++;
                }
            }
        }

        if(sea == n * m || r - l == n * m)
        {
            return -1;
        }

        //遍历
        int level = 0;
        while(l < r)
        {
            level++;
            int size = r - l;
            for(int k = 0, x, y, nx, ny; k < size; k++)
            {
                x = q[l][0];
                y = q[l++][1];
                for(int i = 0; i < 4; i++)//上下左右加进队列
                {
                    nx = x + move[i];
                    ny = y + move[i + 1];
                    if(nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 0 && visited[nx][ny] == false)
                    {
                        visited[nx][ny] = true;
                        q[r][0] = nx;
                        q[r++][1] = ny;
                    }
                }
            }
        }
        
        return level - 1;
    }
};