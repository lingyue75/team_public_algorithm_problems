class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        //双向广搜(bfs小优化) 模板
        //1.从头从尾， 谁小走谁
        unordered_set<string> dict(wordList.begin(), wordList.end());
        unordered_set<string> biglevel;
        unordered_set<string> smalllevel;
        unordered_set<string> nextlevel;

        biglevel.insert(endWord);
        smalllevel.insert(beginWord);
        if(!dict.count(endWord))
        {
            return 0;
        }
        //bfs
        for(int len = 2; smalllevel.size() != 0; len++)
        {
            for(auto s : smalllevel)
            {
                string tmp = s;
                for(int i = 0; i < s.size(); i++)
                {
                    char old = tmp[i];
                    for(char ch = 'a'; ch <= 'z' ; ch++)
                    {
                        tmp[i] = ch;
                        if(biglevel.count(tmp))//大小level 有同一元素返回, 先查再删
                        {
                            return len;
                        }
                        if(dict.count(tmp) && ch != old)
                        {
                            nextlevel.insert(tmp);
                            dict.erase(tmp);
                        }
                    }
                    tmp[i] = old;//还回去
                }
            }

            if(nextlevel.size() > biglevel.size())//谁小谁搜
            {
                smalllevel.swap(biglevel);
                biglevel.swap(nextlevel);
                nextlevel.clear();
            }
            else
            {
                smalllevel.swap(nextlevel);
                nextlevel.clear();
            }
        }
        
        return 0;
    }
};