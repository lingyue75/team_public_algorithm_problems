const int MAXN = 2500 + 10;
int tree[MAXN][26] = {0};
int pass[MAXN] = {0};
int End[MAXN] = {0};
int cnt = 1;
unordered_map<string,int> um;
class MapSum {
public:
    
    MapSum() {
        cnt = 1;     const int MAXN = 2500 + 10;
int tree[MAXN][26] = {0};
int pass[MAXN] = {0};
int End[MAXN] = {0};
int cnt = 1;
unordered_map<string,int> um;
class MapSum {
public:
    
    MapSum() {
        cnt = 1;     
    }
    
    void insert(string key, int val) {
        //val就是pass了多少次
        int diff = val - um[key];//更新val
        int n = key.size();
        int cur = 0;
        for(int i = 0,path; i < n; i++)
        {
            path = key[i] - 'a';
            if(tree[cur][path] == 0)
            {
                tree[cur][path] = cnt++;
            }
            cur = tree[cur][path];
            pass[cur] += diff;
        }
        um[key] = val;
    }
    
    int sum(string prefix) {
        //最后+=pass
        int ans = 0;
        int n = prefix.size();
        int cur = 0;
        for(int i = 0,path; i < n; i++)
        {
            path = prefix[i] - 'a';
            if(tree[cur][path] == 0)
            {
                return 0;
            }
            cur = tree[cur][path];
        }
        ans += pass[cur];
        return ans;
    }
    ~MapSum()//习惯全局变量所以写了个析构函数,注释里能看出是可以这么写的
    {
        um.clear();
        for(int i = 0; i < cnt; i++)
        {
            memset(tree[i], 0, sizeof(tree[i]));
            pass[i] = 0;
            End[i] = 0;
        }
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
    }
    
    void insert(string key, int val) {
        //val就是pass了多少次
        int diff = val - um[key];//更新val
        int n = key.size();
        int cur = 0;
        for(int i = 0,path; i < n; i++)
        {
            path = key[i] - 'a';
            if(tree[cur][path] == 0)
            {
                tree[cur][path] = cnt++;
            }
            cur = tree[cur][path];
            pass[cur] += diff;
        }
        um[key] = val;
    }
    
    int sum(string prefix) {
        //最后+=pass
        int ans = 0;
        int n = prefix.size();
        int cur = 0;
        for(int i = 0,path; i < n; i++)
        {
            path = prefix[i] - 'a';
            if(tree[cur][path] == 0)
            {
                return 0;
            }
            cur = tree[cur][path];
        }
        ans += pass[cur];
        return ans;
    }
    ~MapSum()//习惯全局变量所以写了个析构函数
    {
        um.clear();
        for(int i = 0; i < cnt; i++)
        {
            memset(tree[i], 0, sizeof(tree[i]));
            pass[i] = 0;
            End[i] = 0;
        }
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */