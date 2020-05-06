#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    double x = (a + b + c) / 3.0;
    printf("%.3lf\n", x);
    return 0;
}