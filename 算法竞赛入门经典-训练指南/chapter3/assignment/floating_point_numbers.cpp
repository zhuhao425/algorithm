#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>

using namespace std;

double const eps = 0.0000001;

int main()
{
    string x;
    while (cin >> x)
    {
        if(x == "0e0")
            break;
        for (int i = 0; i < x.length();++i)
            if(x[i] == 'e')
            {
                x[i] = ' ';
                break;
            }
        double a;
        int b;
        sscanf(x.c_str(), "%lf %d", &a, &b);
        double ans = b + log10(a);
        for (int m = 0; m <= 9; ++m)
            for (int e = 1; e <= 30;++e)
            {
                double tmp = log10((1 << m + 1) - 1) + ((1 << e) - 2 - m) * log10(2);
                if(abs(tmp - ans) <= eps)
                {
                    cout << m << " " << e << endl;
                    break;
                }
            }
    }
    return 0;
}