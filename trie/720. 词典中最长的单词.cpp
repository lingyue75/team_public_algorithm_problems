const int MAXN = 30 * 1000 + 5;
int tree[MAXN][26] = {0};
int cnt = 1;
int End[MAXN] = {0};
class Solution {
public:
    void Build()
    {
        cnt = 1;
    }
    void Clear()
    {
        for(int i = 0; i < cnt; i++)
        {
            memset(tree[i], 0, sizeof(tree[i]));
            End[i] = 0;
        }
    }
    string longestWord(vector<string>& words) {
        //按串长度排序，然后建trie，每个字符进去顺路判断是否合法
        sort(words.begin(), words.end(), [&](auto& a, auto& b){
            if(a.size() != b.size()) return a.size() < b.size();
            else return a < b;
        });
        Build();
        End[0] = 1;
        int n = words.size();

        int mx = 0;
        string ans;
        for(auto word : words)
        {
            int flag = 0;//路中标记，如果一路上end都大于0，那么就是合法字符串
            int sz = 0;//长的才换
            int cur = 0;
            for(int i = 0,path; i < word.size(); i++)
            {
                path = word[i] - 'a';
                if(tree[cur][path] == 0)
                {
                    tree[cur][path] = cnt++;
                }
                if(End[cur] == 0)
                {
                    flag = 1;
                }
                sz ++;
                cur = tree[cur][path];
            }   
            End[cur]++;
            if(flag == 0 && sz > mx)
            {
                mx = sz;
                ans = word;
            }
        }   
        Clear();
        return ans;
    }
};