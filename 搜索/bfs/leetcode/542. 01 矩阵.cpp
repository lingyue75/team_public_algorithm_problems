const int MAXN = 1e4 + 5;
vector<array<int, 2>> q(MAXN);
bool visited[MAXN][MAXN] = {false};
int Move[] = {-1, 0, 1, 0, -1};
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        for(int i = 0; i < n; i++)
        {
            memset(visited[i], false, sizeof(visited[i]));
        }
        int l = 0, r = 0;
        //多源bfs, 源是0 先遍历
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(mat[i][j] == 0)
                {
                    q[r][0] = i;
                    q[r++][1] = j;
                    visited[i][j] = true;
                }
            }
        }

        vector<vector<int>> ans(n, vector<int>(m, 0));
        //然后对 所有0 bfs
        //这里的逻辑是  1离0多远就是答案
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
                    if(nx >= 0 && nx < n && ny >= 0 && ny < m && visited[nx][ny] != true && mat[nx][ny] == 1)
                    {
                        //把得到答案的1 也放进队列
                        ans[nx][ny] = level;
                        q[r][0] = nx;
                        q[r++][1] = ny;
                        visited[nx][ny] = true;//自身标记不重复遍历
                    }
                }
            }
        }
        return ans;
    }
};