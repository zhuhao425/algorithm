#include <cstdio>
#include <iostream>

using namespace std;

int sum1(int* begin,int* end)
{
    int n = end - begin;
    int ans = 0;
    for (int i = 0; i < n;++i)
        ans += begin[i];
    return 0;
}

int sum2(int* begin,int* end)
{
    int ans = 0;
    for (int *p = begin; p != end;++p)
        ans += *p;
    return ans;
}

int main()
{
    int n, a[100];
    scanf("%d", &n);
    for (int i = 0; i < n;++i)
        scanf("%d", &a[i]);
    printf("%d\n", sum1(&a[1],&a[n - 1]));
    printf("%d\n", sum2(&a[1],&a[n - 1]));
    return 0;
}