#include <cstdio>
#include <iostream>

using namespace std;

void swap(int a,int b)
{
    int t = a;
    a = b;
    b = t;
}

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    swap(a,b);
    printf("%d %d\n", a, b);
    return 0;
}