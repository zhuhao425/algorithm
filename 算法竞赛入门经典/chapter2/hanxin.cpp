#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
    int a, b, c;
    int t = 0;
    while (cin >> a >> b >> c)
    {
        printf("Case %d: ",++t);
        int x = 0;
        for (int i = 10; i <= 100; ++i)
        {
            if(i % 3 == a && i % 5 == b && i % 7 ==c)
            {
                x = i;
                break;
            }
        }
        if(x != 0)
            printf("%d\n", x);
        else
            puts("No answer");
    }
    return 0;
}