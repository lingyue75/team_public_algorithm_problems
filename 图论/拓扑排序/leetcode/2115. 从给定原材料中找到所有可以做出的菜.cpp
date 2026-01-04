unordered_map<string, unordered_set<string>> graph;
unordered_map<string, int> indegree;
class Solution {
public:
    void Build()
    {
        graph.clear();
        indegree.clear();
    }

    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        //拓扑排序
        
        //1.建图, 同时加入度
        int n = recipes.size();
        
        Build();
        for(int i = 0; i < n; i++)
        {
            for(auto s : ingredients[i])
            {
                graph[s].insert(recipes[i]);
                indegree[recipes[i]]++;
            }
        }
        vector<string> ans;
        //supplies直接当入度为0的释放节点
        deque<string> q(supplies.begin(), supplies.end());
        while(q.size() != 0)
        {
            string s1 = q.front();
            q.pop_front();
            for(auto s2 : graph[s1])
            {
                if(--indegree[s2] == 0)//同时可以作为原材料
                {
                    q.push_back(s2);
                    ans.push_back(s2);
                }
            }
        }
        return ans;
    }
};