#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n;++i)
        printf("%d\n", 2 * i);
    
    for (int i = 2; i <= 2 * n;i += 2)
        printf("%d\n", i);
    
    return 0;
}