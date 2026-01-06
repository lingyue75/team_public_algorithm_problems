class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        //单源最短路 最大值 dj算法
        //1.dis vis 小堆
        int m = times.size();
        vector<int> dis(n + 1, INT_MAX);//1-n个点
        vector<bool> vis(n + 1, false);

        auto cmp = [&](auto& a, auto& b){
            return a[1] > b[1];
        };
        priority_queue<array<int,2>, vector<array<int, 2>>, decltype(cmp)> hp(cmp);

        //2.建图
        vector<vector<array<int, 2>>> graph(n + 1);//1-n个点
        for(auto s : times)
        {
            graph[s[0]].push_back({s[1], s[2]});
        }

        //3.弹
        hp.push({k, 0});
        dis[k] = 0;
        while(hp.size() != 0)
        {
            int u = hp.top()[0];
            hp.pop();
            if(vis[u])//弹过不管
            {
                continue;
            }
            vis[u] = true;//现在弹过了
            for(auto s : graph[u])//遍历
            {
                int v = s[0];
                int w = s[1];
                if(!vis[v] && dis[u] + w < dis[v])//没弹过 且 dis小
                {
                    //dis更新 入堆
                    dis[v] = dis[u] + w;
                    hp.push({v, dis[v]});
                } 
            }
        }
        int mx = *max_element(dis.begin() + 1, dis.end());
        return mx == INT_MAX ? -1 : mx;
    }
};