#include <cstdio>
#include <iostream>

using namespace std;

int sum(int a[],int n)
{
    int ans = 0;
    for (int i = 0; i < n;++i)
        ans += a[i];
    return ans;
}

int main()
{
    int n,a[100];
    scanf("%d", &n);
    for (int i = 0; i < n;++i)
        scanf("%d", &a[i]);
    int ans = sum(a,n);
    printf("%d\n", ans);
    return 0;
}