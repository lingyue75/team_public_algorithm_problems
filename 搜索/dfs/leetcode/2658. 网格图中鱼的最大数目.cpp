class Solution {
public:
    int dfs(vector<vector<int>>& grid, int i, int j, int n, int m)
    {
        if(i < 0 || i >= n || j < 0 || j >= m || grid[i][j] == 0)
        {
            return 0;
        }
        int cnt = grid[i][j];
        grid[i][j] = 0;//防止重复dfs 
        return cnt + dfs(grid, i - 1, j, n, m) + dfs(grid, i + 1, j, n, m) + dfs(grid, i, j - 1, n, m) + dfs(grid, i, j + 1, n, m);
    }
    int findMaxFish(vector<vector<int>>& grid) {
        //数据量很小 直接爆搜
        int n = grid.size();
        int m = grid[0].size();
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(grid[i][j] != 0)
                {
                    int ret = dfs(grid, i, j, n, m);
                    ans = max(ans, ret);
                }
            }
        }

        return ans;
    }
};