#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    double f;
    cin >> f;
    double c = 5.0 * (f - 32) / 9;
    printf("%.3lf\n", c);
    return 0;
}