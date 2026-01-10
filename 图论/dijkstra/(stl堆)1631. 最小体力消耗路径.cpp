class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        //单源最短路 dj
        int n = heights.size();
        int m = heights[0].size();
        auto cmp = [&](auto& a, auto& b){
            return a[2] > b[2];
        };
        priority_queue<array<int, 3>, vector<array<int, 3>>, decltype(cmp)> heap(cmp);
        vector<vector<int>> distances(n, vector<int>(m, INT_MAX));
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int Move[] = {-1, 0, 1, 0, -1};


        heap.push({0, 0, 0});
        while(heap.size() != 0)
        {
            int x = heap.top()[0];
            int y = heap.top()[1];
            int c = heap.top()[2];
            heap.pop();
            if(visited[x][y])
            {
                continue;
            }
            if(x == n - 1 && y == m - 1)
            {
                return c;
            }
            visited[x][y] = true;
            for(int i = 0, nx, ny, nc; i < 4; i++)
            {
                nx = x + Move[i];
                ny = y + Move[i + 1];
                if(nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) //在合法下标且没弹过
                {
                    nc = max(abs(heights[x][y] - heights[nx][ny]), c);
                    heap.push({nx, ny, nc});
                }
            }
        }
        return -1;
    }
};