const int MAXN = 1e4 + 10;
vector<array<int, 2>> q(MAXN);
bool visited[105][105];
int Move[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1} ,          {0, 1} ,
    {1, -1} , {1, 0} , {1, 1}
};
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        //标准单源bfs
        int n = grid.size();
        int m = grid[0].size();
        if(n * m == 1 && grid[0][0] == 0)
        {
            return 1;
        }
        if(grid[n - 1][m - 1] == 1 || grid[0][0] == 1)
        {
            return -1;
        }
        for(int i = 0; i < n; i++)
        {
            fill(visited[i], visited[i] + m, false);
        }
        int l = 0, r = 0;

        q[r][0] = 0;
        q[r++][1] = 0;
        visited[0][0] = true;
        int level = 1;
        while(l < r)
        {
            level++;
            int sz = r - l;
            for(int k = 0, x, y; k < sz; k++)
            {
                x = q[l][0];
                y = q[l++][1];
                //8方向搜
                for(int i = 0, nx, ny; i < 8; i++)
                {
                    nx = x + Move[i][0];
                    ny = y + Move[i][1];
                    if(nx >= 0 && nx < n && ny >= 0 && ny < m && visited[nx][ny] != true && grid[nx][ny] == 0)
                    {
                        q[r][0] = nx;
                        q[r++][1] = ny;
                        visited[nx][ny] = true;
                        if(nx == n - 1 && ny == m - 1)
                        {
                            return level;
                        }
                    }
                }
            }
        }
        return -1;
    }
};