//https://leetcode.cn/problems/pond-sizes-lcci/description/
class Solution {
public:
    int dfs(int n, int m, int i, int j, vector<vector<int>>& land)
    {
        if(i < 0 || i >= n || j < 0 || j >= m || land[i][j] != 0)
        {
            return 0;
        }
        land[i][j] = 1;
        return 1 + dfs(n, m, i - 1, j - 1, land) +  dfs(n, m, i - 1, j, land) +  dfs(n, m, i - 1, j + 1, land) +
                   dfs(n, m, i, j - 1, land)                                  +  dfs(n, m, i, j + 1, land) +
                   dfs(n, m, i + 1, j - 1, land) +  dfs(n, m, i + 1, j, land) +  dfs(n, m, i + 1, j + 1, land);
    }

    vector<int> pondSizes(vector<vector<int>>& land) {
        //爆搜，是0进dfs然后染色为1防止重复
        int n = land.size();
        int m = land[0].size();
        vector<int> ans;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(land[i][j] == 0)
                {
                    int ret = dfs(n, m, i, j, land);
                    ans.push_back(ret);
                }
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};