const int MAXN = 1e4 + 10;
vector<array<int, 2>> q(MAXN);
vector<int> Move = {-1, 0, 1, 0, -1};
bool visited[105][105] = {false};
class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        
        int l = 0, r = 0;
        //单源bfs
        int n = maze.size();
        int m = maze[0].size();
        for(int i = 0; i < n; i++)
        {
            fill(visited[i], visited[i] + m, false);
        }
        q[r][0] = entrance[0];
        q[r++][1] = entrance[1];
        visited[entrance[0]][entrance[1]] = true;
        int level = 0;
        while(l < r)
        {
            level++;
            int sz = r - l; 
            for(int j = 0; j < sz; j++)
            {
                int x = q[l][0];
                int y = q[l++][1];
                for(int i = 0, nx, ny; i < 4; i++)
                {
                    nx = x + Move[i];
                    ny = y + Move[i + 1];
                    if(nx >= 0 && nx < n && ny >= 0 && ny < m && visited[nx][ny] != true && maze[nx][ny] == '.')
                    {
                        q[r][0] = nx;
                        q[r++][1] = ny;
                        visited[nx][ny] = true;
                        if(nx == 0 || ny == 0 || nx == n - 1 || ny == m - 1)
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