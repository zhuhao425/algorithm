#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int n;
    cin >> n;
    double x = n * 95;
    if(x >= 300)
        x *= 0.85;
    printf("%.2lf\n", x);
    return 0;
}