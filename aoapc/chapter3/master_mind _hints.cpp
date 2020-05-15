#include <unordered_map>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int n;
    int t = 1;
    while (cin >> n)
    {
        if(n == 0)
            break;
        vector<int> nums(n, 0);
        unordered_map<int, int> mp;
        for (int i = 0; i < n; ++i)
        {
            cin >> nums[i];
            unordered_map<int, int>::iterator it = mp.find(nums[i]);
            if(it == mp.end())
                mp.insert(make_pair(nums[i],1));
            else
                ++it->second;
        }
        printf("Game %d:\n", t++);
        while (true)
        {
            vector<int> mark(n,0);
            for (int i = 0; i < n; ++i)
                cin >> mark[i];
            bool tag = false;
            for (int i = 0; i < n; ++i)
                if(mark[i] != 0)
                {
                    tag = true;
                    break;
                }
            if(!tag)
                break;
            int strong = 0;
            int weak = 0;
            unordered_map<int, int> need = mp;
            for (int i = 0; i < n; ++i)
            {
                unordered_map<int, int>::iterator it = need.find(mark[i]);
                if (nums[i] == mark[i])
                {
                    ++strong;
                    --it->second;
                    if(it->second == 0)
                        need.erase(mark[i]);
                }
            }
            for (int i = 0; i < n; ++i)
            {
                unordered_map<int, int>::iterator it = need.find(mark[i]);
                if (nums[i] == mark[i])
                    continue;
                else
                {
                    if(it != need.end())
                    {
                        --it->second;
                        ++weak;
                        if(it->second == 0)
                            need.erase(mark[i]);
                    }
                }
            }
            printf("    (%d,%d)\n", strong, weak);
        }
    }
    return 0;
}