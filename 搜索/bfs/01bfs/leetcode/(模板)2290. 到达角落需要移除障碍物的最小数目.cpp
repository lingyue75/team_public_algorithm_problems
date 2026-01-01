int Move[] = {-1, 0, 1, 0, -1};
class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        //01 bfs模板
        //1.设置distance 数组全部初始化为最大
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> distance(n, vector<int>(m, INT_MAX));
        /*for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                distance[i][j] = INT_MAX;
            }
        }*/

        //2.创建双端队列， 源点进, distance 改
        deque<array<int, 2>> dq;
        dq.push_front({0,0});
        distance[0][0] = 0;
        //3.弹 直到队列为空
        while(dq.size() != 0)
        {
            int x = dq.front()[0];
            int y = dq.front()[1];
            dq.pop_front();
            //4.是目标点就直接返回
            if(x == n - 1 && y == m - 1)
            {
                return distance[x][y];
            }
            for(int i = 0, nx, ny; i < 4; i++)
            {
                nx = x + Move[i];
                ny = y + Move[i + 1];
                if(nx >= 0 && nx < n && ny >= 0 && ny < m && distance[x][y] + grid[nx][ny] < distance[nx][ny])//不越界且distance 小就更新
                {
                    distance[nx][ny] = distance[x][y] + grid[nx][ny];
                    if(grid[nx][ny] == 0)// 可以覆盖，从头进
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