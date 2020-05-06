#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    int m = (n % 10) * 100 + (n / 10 % 10) * 10 + n / 100;
    printf("%03d\n", m);
    return 0;
}