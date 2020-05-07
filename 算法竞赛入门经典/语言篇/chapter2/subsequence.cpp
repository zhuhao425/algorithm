#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
    int n, m;
    int t = 0;
    while (cin >> n >> m)
    {
        if (n == 0 && m == 0)
            break;
        printf("Case %d: ", ++t);
        double sum = 0;
        for (int i = n; i <= m; ++i)
        {
            double term = 1.0 / (i * 1.0 * i);
            sum += term;
        }
        printf("%.5lf\n", sum);
    }
    return 0;
}