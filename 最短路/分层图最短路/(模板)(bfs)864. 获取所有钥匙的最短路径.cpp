const int MAXN = 35;
const int MAXM = 35;
const int MAXK = 6;
bool visited[MAXN][MAXM][1 << MAXK] = {false};
vector<array<int, 3>> q(MAXN * MAXM * (1 << MAXK));
int l, r, key;

class Solution {
public:
    void Build(vector<string>& grid)
    {
        l = 0; r = 0;
        key = 0;
        int n = grid.size();
        int m = grid[0].size();

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                fill(visited[i][j], visited[i][j] + (1 << MAXK), false);
            }
        }

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(grid[i][j] == '@')
                {
                    q[r][0] = i;
                    q[r][1] = j;
                    q[r++][2] = 0;
                }
                if(grid[i][j] >= 'a' && grid[i][j] <= 'z')
                {
                    key |= (1 << (grid[i][j] - 'a'));
                }
            }
        }
    }

    int shortestPathAllKeys(vector<string>& grid) {
        //bfs分层图最短路
        //本质是多一维信息存状态  
        Build(grid);
        int Move[] = {-1, 0, 1, 0, -1};
        int n = grid.size();
        int m = grid[0].size();
        int level = 1;
        while(l < r)
        {
            int sz = r - l;
            for(int k = 0; k < sz; k++)//把一个扩散处理完才是下一个level
            {
                int x = q[l][0];
                int y = q[l][1];
                int s = q[l++][2];
                visited[x][y][s] = true;
                for(int i = 0, nx, ny, ns; i < 4; i++)
                {
                    nx = x + Move[i];
                    ny = y + Move[i + 1];
                    ns = s;
                    
                    if(nx < 0 || nx >= n || ny < 0 || ny >= m || grid[nx][ny] == '#' || visited[nx][ny][ns] == true)//越界或者走过continue
                    {
                        continue;
                    }
                    if(grid[nx][ny] >= 'A' && grid[nx][ny] <= 'Z' && ((ns & (1 << (grid[nx][ny] - 'A'))) == 0))//是锁没钥匙continue
                    {
                        continue;
                    }
                    if(grid[nx][ny] >= 'a' && grid[nx][ny] <= 'z')//是钥匙
                    {
                        ns |= 1 << (grid[nx][ny] - 'a');
                        if(ns == key)
                        {
                            return level;
                        }
                    }
                    visited[nx][ny][ns] = true;
                    q[r][0] = nx;
                    q[r][1] = ny;
                    q[r++][2] = ns;
                } 
            } 
            level++;
        }
        return -1;
    }
};