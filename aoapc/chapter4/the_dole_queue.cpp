#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

void getNext(vector<int>& mark,int& index,int direct,int step)
{
    int k = step;
    while(k > 0)
    {
        if(direct == 0)
        {
            ++index;
            if(index >= mark.size())
                index -= mark.size();
        }
        else
        {
            --index;
            if(index < 0)
                index += mark.size();
        }
        if(mark[index] == 0)
            continue;
        else
            --k;
    }
}

int main()
{
    int n, k, m;
    while (cin >> n >> k >> m)
    {
        if(n == 0 && k == 0 && m == 0)
            break;
        vector<int> mark(n,1);
        int l = -1;
        int r = n;
        int count = n;
        int t = 0;
        while (count > 0)
        {
            getNext(mark, l, 0, k);
            getNext(mark,r,1,m);
            mark[l] = 0;
            mark[r] = 0;
            if (t != 0)
                cout << ",";
            if(l == r)
            {
                --count;
                printf("% 3d", l + 1);
            }
            else
            {
                count -= 2;
                printf("% 3d% 3d", l + 1, r + 1);
            }
            ++t;
        }
        cout << endl;
    }
    return 0;
}