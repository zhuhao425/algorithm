#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 1010

int a[MAXN];

int main()
{
    int n, k, first = 1;
    memset(a, 0, sizeof(a));
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= k;++i)
        for (int j = 1; j <= n;++j)
            if(j % i == 0)
                a[j] = !a[j];

    for (int i = 1; i <= n;++i)
        if(a[i])
        {
            if(first)
                first = 0;
            else
                printf(" ");
            printf("%d", i);
        }
    printf("\n");
    return 0;
}