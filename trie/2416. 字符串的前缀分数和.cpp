const int MAXN = 1e6 + 10;
const int MAXM = 1e6 + 10;
int tree[MAXN][26] = {0};
int pass[MAXM] = {0};
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
            pass[cur]++;
        }
    }

    int Search(string& s)
    {
        int n = s.size();
        int cur = 0;
        int ret = 0;
        for(int i = 0, path; i < n; i++)
        {
            path = s[i] - 'a';
            if(tree[cur][path] == 0)
            {
                return ret;
            }
            cur = tree[cur][path];
            ret += pass[cur];
        }
        return ret;
    }

    void Clear()
    {
        for(int i = 0; i < cnt; i++)
        {
            memset(tree[i], 0, sizeof(tree[i]));
            pass[i] = 0;
        }
    }

    vector<int> sumPrefixScores(vector<string>& words) {
        //建trie，pass求和
        int n = words.size();
        cnt = 1;
        for(auto word : words)
        {
            Insert(word);
        }
        vector<int> ans(n);
        int idx = 0;
        for(auto word : words)
        {
            ans[idx++] = Search(word);
        }
        Clear();
        return ans;
    }
};