#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int a = (4 * n - m) / 2;
    int b = n - a;
    if (m % 2 == 1 || a < 0 || b < 0)
        printf("No answer\n");
    else
        printf("%d %d\n",a,b);
    return 0;
}