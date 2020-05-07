#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
    double i;
    for (int i = 0; i != 10; i += 0.1)
        printf("%.1f\n", i);
    return 0;
}