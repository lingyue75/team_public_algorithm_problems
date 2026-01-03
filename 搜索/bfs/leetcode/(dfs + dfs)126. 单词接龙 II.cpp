unordered_set<string> dict;
unordered_set<string> curlevel;
unordered_set<string> nextlevel;
unordered_map<string, unordered_set<string>> graph;//反向图用于dfs
list<string> path;
vector<vector<string>> ans;

class Solution {
public:
    void Build(vector<string>& wordList)
    {
        dict.clear();
        for(auto s : wordList)
        {
            dict.insert(s);
        }
        curlevel.clear();
        nextlevel.clear();
        graph.clear();
        path.clear();
        ans.clear();
    }

    bool bfs(string beginWord, string endWord)
    {
        curlevel.insert(beginWord);
        bool find = false;

        while(curlevel.size() != 0)
        {
            for(auto s : curlevel)//防止重复添加路径
            {
                dict.erase(s);
            }

            for(auto s : curlevel)
            {
                string w = s;
                for(int i = 0; i < s.size(); i++)
                {
                    char old = s[i];
                    for(char ch = 'a'; ch <= 'z'; ch++)
                    {
                        s[i] = ch;
                        if(dict.count(s) && w != s)//建反图
                        {
                            if(s == endWord)
                            {
                                find = true;
                            }
                            graph[s].insert(w);
                            nextlevel.insert(s);
                        }
                    }
                    s[i] = old;
                }
            }
            if(find == true)//这一层全部到目标的图全建完了，返回
            {
                return true;
            }
            else//接着找
            {
                curlevel = nextlevel;
                nextlevel.clear();
            }
        }
        return false;
    }

    void dfs(string word, string aim)
    {
        path.push_front(word);//建路径
        if(word == aim)
        {
            vector<string> tmp(path.begin(), path.end());
            ans.push_back(tmp);
        }
        else if(graph.count(word))
        {
            for(auto s : graph[word])
            {
                dfs(s, aim);
            }
        }

        path.pop_front();//回溯 维护现场
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        //bfs + dfs
        Build(wordList);//查找不方便， 把wordList变成uset

        if(!dict.count(endWord))
        {
            return ans;
        }
        if(bfs(beginWord, endWord))//找到了就dfs 顺路把反向图建好
        {
            dfs(endWord, beginWord);
        }
        return ans;
    }
};