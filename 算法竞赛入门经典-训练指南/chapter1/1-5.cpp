#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int main()
{
    const double pi = acos(-1.0);
    double r,h;
    scanf("%lf %lf",&r,&h);
    double s1 = pi * r * r;
    double s2 = 2 * pi * r * h;
    double s = s1 * 2 + s2;
    printf("Area = %.3f\n",s);
    return 0;
}