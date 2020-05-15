#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int a, b, c;
    int t = 0;
    while (cin >> a >> b >> c)
    {
        if(a == 0 && b == 0 && c == 0)
            break;

        int x = a / b;
        int tmp = a % b;
        printf("Case %d: %d.", ++t, x);
        while (c--)
        {
            if(tmp < b)
                tmp *= 10;
            int y = tmp / b;
            tmp %= b;
            if(c != 0)
                printf("%d", y);
            else
            {
                if(tmp < b)
                    tmp *= 10;
                if(tmp / b >= 5)
                    ++y;
                printf("%d", y);
            }
        }
        puts("");
    }
    return 0;
}