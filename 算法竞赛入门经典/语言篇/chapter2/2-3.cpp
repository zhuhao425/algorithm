#include <cstdio>
#include <cmath>
#include <iostream>

using namespace std;

int main()
{
    for (int x = 1;;++x)
    {
        int n = x * x;
        if(n < 1000)
            continue;
        if(n > 9999)
            break;
        int low = n % 100;
        int high = n / 100;
        if(low / 10 == low % 10 && high / 10 == high % 10)
            printf("%d\n", n);
    }
    return 0;
}