const int MAXN = 1e6 + 10;
int tree[MAXN][26] = {0};
int End[MAXN];
int cnt = 0;
class Solution {
public:
    void Insert(string& s)
    {
        int cur = 0;
        int n = s.size();
        for(int i = 0, path; i < n; i++)
        {
            path = s[i] - 'a';
            if(tree[cur][path] == 0)
            {
                tree[cur][path] = ++cnt;
            }
            cur = tree[cur][path];
        }
        End[cur]++;
    }
    int Search(string& s)
    {   
        int cur = 0;
        int n = s.size();
        int sz = 0;
        for(int i = 0, path; i < n; i++)
        {
            path = s[i] - 'a';
            if(End[cur] > 0 || tree[cur][path] == 0)//如果有词根了就直接输出
            {
                return End[cur] > 0 ? sz : 0;
            }
            sz++;
            cur = tree[cur][path];
        }
        return End[cur] > 0 ? sz : 0;
    }
    void Clear()
    {
        for(int i = 0; i <= cnt; i++)
        {
            memset(tree[i], 0, sizeof(tree[i]));
            End[i] = 0;
        }
    }
    string replaceWords(vector<string>& dictionary, string sentence) {
        cnt = 0;
        int n = dictionary.size();
        for(int i = 0; i < n; i++)//词典建树,在树上的就输出只在树上的词根，否则全部输出
        {
            Insert(dictionary[i]);
        }
        vector<string> s;
        string token;
        istringstream ss(sentence);
        while(getline(ss, token, ' '))//分割字符串
        {
            s.push_back(token);
        }
        string ans;
        for(auto word : s)
        {
            int sz = Search(word);
            if(sz == 0)
            {
                ans += word + " ";
            }
            else
            {
                ans += word.substr(0, sz) + " ";
            }
        }
        ans.pop_back();
        Clear();
        return ans;  
    }
};