#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(vector<int> a,vector<int> b)
{
    if(a[0] != b[0])
        return a[0] < b[0];
    else
        return a[1] < b[1];
}

bool check(vector<vector<int>>& triangle)
{
    for (int i = 0; i < 6; i += 2)
    {
        if(triangle[i][0] != triangle[i + 1][0])
            return false;
        if(triangle[i][1] != triangle[i + 1][1])
            return false;
    }
    return true;
}

int main()
{
    vector<vector<int>> triangle(6,vector<int>{0,0});
    while (cin >> triangle[0][0] >> triangle[0][1])
    {
        if(triangle[0][0] > triangle[0][1])
            swap(triangle[0][0],triangle[0][1]);
        for (int i = 1; i < 6;++i)
        {
            cin >> triangle[i][0] >> triangle[i][1];
            if(triangle[i][0] > triangle[i][1])
                swap(triangle[i][0],triangle[i][1]);
        }
        sort(triangle.begin(), triangle.end(), cmp);
        bool tag = true;
        if(!check(triangle))
            tag = false;
        if(triangle[0][0] != triangle[2][0])
            tag = false;
        if(triangle[0][1] != triangle[4][0])
            tag = false;
        if(triangle[2][1] != triangle[4][1])
            tag = false;
        if (!tag)
            puts("IMPOSSIBLE");
        else
            puts("POSSIBLE");
    }
    return 0;
}