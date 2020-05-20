#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

bool is_prime(int n)
{
    if(n <= 1)
        return false;
    int m = floor(sqrt(n) + 0.5);
    for (int i = 2; i <= m; ++i)
        if(n % i == 0)
            return false;
    return true;
}

int main()
{
    int n;
    scanf("%d", &n);
    if(is_prime(n))
        printf("%d is a prime.\n",n);
    else
        printf("%d is not a prime.\n", n);
    return 0;
}