#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    int t = a;
    a = b;
    b = t;
    printf("%d %d\n", a, b);
    return 0;
}