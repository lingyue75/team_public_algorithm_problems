

class Solution {
public:
    vector<string> partitionString(string s) {
        //单个字符串的trie插入, 新段就加入ans,然后重头走
        const int MAXN = 1e5 + 5;
        int tree[MAXN][26] = {0};
        int n = s.size();
        int cnt = 1;
        vector<string> ans;
        string str;
        int cur = 0;
        for(int i = 0, path; i < n; i++)
        {
            path = s[i] - 'a';
            str += (path + 'a'); 
            if(tree[cur][path] == 0)
            {
                tree[cur][path] = cnt++; 
                ans.push_back(str);
                str = "";
                cur = 0;
            }
            else cur = tree[cur][path];
        }
        return ans;
    }
};