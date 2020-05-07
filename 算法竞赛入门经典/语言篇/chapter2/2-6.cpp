#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    double sum = 0;
    int i = 0;
    do
    {
        double term = 1.0 / (i * 2 + 1);
        if (i % 2 == 0)
            sum += term;
        else
            sum -= term;
        ++i;
    } while (1.0 / (i * 2 + 1) >= 1e-6);
    printf("%lf\n", sum);
    return 0;
}