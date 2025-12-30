//思路：先模拟，发现顺序无关排完序后好做，那就先排序，然后再试每个贴纸的时候，发现和bfs很像
//那就bfs,然后可以剪枝，先把前面的第一个字母全干了，这样可以防止有些用不到的贴纸也试，然后咋维护
//对每个字母建邻接表存相应贴纸，然后bfs就好了，还有一个剪枝是 不把存过的中间态又放进队列里，然后处理就行
const int MAXN = 750;
vector<vector<string>> graph(26);
vector<string> q(MAXN);
unordered_set<string> visited;
class Solution {
public:
    string nx(string s1, string s2)
    {
        int l1 = 0, l2 = 0;
        int n1 = s1.size(), n2 = s2.size();
        string ret;
        while(l1 < n1 && l2 < n2)
        {
            if(s1[l1] < s2[l2])
            {
                ret += s1[l1++];
            }
            else if(s1[l1] > s2[l2])
            {
                l2++;
            }
            else
            {
                l1 ++;l2 ++;
            }
        }
        while(l1 < n1)
        {
            ret += s1[l1++];
        }
        return ret;
    }
    int minStickers(vector<string>& stickers, string target) {
        //过程模拟看下来就是可以bfs,因为可以剪，所以顺序不重要，排个序先，排序能剪枝

        //先清空
        for(int i = 0; i < 26; i++)
        {
            graph[i].clear();
        }
        visited.clear();
        int l = 0, r = 0;
        //加贴纸
        for(auto& s : stickers)
        {
            int n = s.size();
            sort(s.begin(), s.end());
            for(int i = 0; i < n; i++)
            {
                if(i == 0 || s[i] != s[i - 1])
                {
                    graph[s[i] - 'a'].push_back(s);
                }
            }
        }

        sort(target.begin(), target.end());

        //bfs
        
        visited.insert(target);
        q[r++] = target;
        int level = 1;
        while(l < r)
        {
            int sz = r - l;
            for(int i = 0; i < sz; i++)
            {
                string cur = q[l++];
                for(auto s : graph[cur[0] - 'a'])
                {
                    string N = nx(cur, s);
                    if(N == "")
                    {
                        return level;
                    }
                    else if(!visited.count(N))
                    {
                        q[r++] = N;
                        visited.insert(N);
                    }
                }
            }
            level++;
        }
        return -1;
    }
};