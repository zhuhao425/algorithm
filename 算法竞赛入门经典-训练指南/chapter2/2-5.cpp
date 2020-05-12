#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
    long long n;
    int count = 0;
    scanf("%lld", &n);
    while(n > 1)
    {
        if(n % 2 == 1)
            n = 3 * n + 1;
        else
            n /= 2;
        ++count;
    }
    printf("%d\n", count);
    return 0;
}