const int MAXN = 2e4 + 10;
int tree[MAXN][26];
vector<set<string>> ids(MAXN);//第i个节点有几个字符串
int cnt = 1;
class Solution {
public:
    void Insert(string& s)
    {
        int n = s.size();
        int cur = 0;
        for(int i = 0, path; i < n; i++)
        {
            path = s[i] - 'a';
            if(tree[cur][path] == 0)
            {
                tree[cur][path] = cnt++;
            }
            cur = tree[cur][path];
            ids[cur].insert(s);
        }
    }

    void Clear()
    {
        for(int i = 0; i < cnt; i++)
        {
            memset(tree[i], 0, sizeof(tree[i]));
            ids[i].clear();
        }
    }
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        //trie + set
        //重复前缀都放在ids里
        cnt = 1;
        int n = products.size();
        for(auto s : products)
        {
            Insert(s);
        }
        int sz = searchWord.size();
        vector<vector<string>> ans(sz);
        //找的时候从ids把前三个放进来
        int cur = 0;
        for(int i = 0, path; i < sz; i++)
        {
            path = searchWord[i] - 'a';
            if(tree[cur][path] == 0)
            {
                break;
            }
            cur = tree[cur][path];
            for(auto str : ids[cur])//最多三个， O(1);
            {
                if(ans[i].size() < 3)
                {
                    ans[i].push_back(str);
                }
                else
                {
                    break;
                }
            }
        }
        Clear();
        return ans;
    }
};