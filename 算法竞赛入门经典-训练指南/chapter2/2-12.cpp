#include <cstdio>
#include <iostream>

using namespace std;

#define INF 1000000000

int main()
{
    int x, n = 0, min = INF, max = -INF, s = 0, kcase = 0;
    while(~scanf("%d",&n) && n)
    {
        int s = 0;
        for (int i = 0; i < n;++i)
        {
            scanf("%d", &x);
            s += x;
            if(x < min)
                min = x;
            if(x < max)
                max = x;
        }
        if(kcase)
            puts("");
        printf("%d %d %.3f\n", min, max, (double)s / n);
    }
    return 0;
}