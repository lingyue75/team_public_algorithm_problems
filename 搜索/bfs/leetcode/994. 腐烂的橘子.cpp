const int MAXN = 105;
vector<array<int, 2>> q(MAXN); 
bool visited[15][15];
int Move[] = {-1, 0, 1, 0, -1};
int l, r;
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        //多源bfs 
        //1.遍历所有腐烂橘子进队列,顺路记一下有多少个好橘子
        int cnt = 0;
        int n = grid.size();
        int m = grid[0].size();
        for(int i = 0; i < n; i++)
        {
            memset(visited[i], false, sizeof(visited[i]));
        }
        l = 0,r = 0;
        for(int i = 0 ; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(grid[i][j] == 2)
                {
                    q[r][0] = i;
                    q[r++][1] = j;
                    visited[i][j] = true;
                }
                if(grid[i][j] == 1)
                {
                    cnt++;
                }
            }
        } 
        if(cnt == 0)
        {
            return 0;
        }
        //2.bfs 每个源4方向搜 是好橘子cnt-- 进队列接着感染 直到为0 不然就不可能
        int level = 0;
        while(l < r)
        {
            level++;
            int sz = r - l;
            for(int k = 0, x, y; k < sz; k++)
            {
                x = q[l][0];
                y = q[l++][1];
                for(int i = 0, nx, ny; i < 4; i++)
                {
                    nx = x + Move[i];
                    ny = y + Move[i + 1];
                    if(nx >= 0 && nx < n && ny >= 0 && ny < m && visited[nx][ny] != true && grid[nx][ny] == 1)
                    {
                        cnt--;
                        if(cnt == 0)
                        {
                            return level;
                        }
                        q[r][0] = nx;
                        q[r++][1] = ny;
                        visited[nx][ny] = true;
                    }
                }
            }
        }
        return -1;
    }
};