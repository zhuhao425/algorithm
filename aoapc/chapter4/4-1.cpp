#include <cstdio>
#include <iostream>

using namespace std;

long long factorial(int n)
{
    long long m = 1;
    for (int i = 1; i <= n;++i)
        m *= i;
    return m;
}

long long c(int n,int m)
{
    return factorial(n) / (factorial(m) * factorial(n - m));
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    printf("%lld\n",c(n,m));
    return 0;
}