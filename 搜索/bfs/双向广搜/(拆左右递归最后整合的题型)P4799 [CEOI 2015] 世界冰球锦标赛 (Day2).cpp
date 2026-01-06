//https://www.luogu.com.cn/problem/P4799
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 45;
const long long MAXM = 1 << 20; 
long long v[MAXN];
long long lsum[MAXM];//左侧可能 2^20
long long rsum[MAXM];//右侧可能 2^20
long long N, M;

int f(int i, int e, long long s, long long w, long long* ans, int j)
{
    if(s > w)//超了返回
    {
        return j;
    }
    if(i == e)//到底了加入ans
    {
        ans[j++] = s;
    }
    else//要 不要递归
    {
        //要v[i]
        j = f(i + 1, e, s + v[i], w, ans, j);
        //不要v[i]
        j = f(i + 1, e, s, w, ans, j);
    }
    return j;//有多少个可能的答案
}

long long count()
{
    int lsize = f(0, N >> 1, 0, M, lsum, 0);//左侧递归有多少结果
    int rsize = f(N >> 1, N, 0, M, rsum, 0);//右侧递归有多少种结果
    sort(lsum, lsum + lsize);
    sort(rsum, rsum + rsize);
    long long ans = 0; 
    //双指针
    for(int i = 0, j = rsize - 1; i < lsize && j >= 0; i++)
    {
        while(j > 0 && lsum[i] + rsum[j] > M)
        {
            j--;
        }
        ans += j + 1;
    }
    return ans;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        cin >> v[i];
    }

    cout << count() << "\n";


    return 0;
}