#include <cstdio>
#include <iostream>

using namespace std;

bool is_prime(int n)
{
    for (int i = 2; i * i <= n; ++i)
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