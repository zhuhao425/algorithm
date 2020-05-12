#include <iostream>
#include <string>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        string x;
        cin >> x;
        double count = 0;
        char tmp = 0;
        for (int i = 0; i < x.length(); ++i)
        {
            if(x[i] >= '0' && x[i] <= '9')
            {
                int nums = 0;
                while(i < x.length() && x[i] >= '0' && x[i] <= '9')
                {
                    nums = nums * 10 + x[i] - '0';
                    ++i;
                }
                double t = 0;
                if (tmp == 'C')
                    t = 12.01;
                else if (tmp == 'H')
                    t = 1.008;
                else if (tmp == 'O')
                    t = 16;
                else if (tmp == 'N')
                    t = 14.01;
                --i;
                count += t * nums;
                tmp = 0;
            }
            else
            {
                if (tmp == 'C')
                    count += 12.01;
                else if (tmp == 'H')
                    count += 1.008;
                else if (tmp == 'O')
                    count += 16;
                else if (tmp == 'N')
                    count += 14.01;
                tmp = x[i];
            }
        }
        if (tmp == 'C')
            count += 12.01;
        else if (tmp == 'H')
            count += 1.008;
        else if (tmp == 'O')
            count += 16;
        else if (tmp == 'N')
            count += 14.01;
        printf("%.3lf\n", count);
    }
    return 0;
}