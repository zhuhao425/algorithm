#include <string>
#include <iostream>

using namespace std;

int getMax(int a,int b)
{
    return a > b ? a : b;
}

int getMin(int a,int b)
{
    return a > b ? b : a;
}

int main()
{
    string a, b;
    while (cin >> a)
    {
        cin >> b;
        int i = 0;
        int x1 = a.length() + b.length();
        for (; i < a.length(); ++i)
        {
            int j = 0;
            for (; j < b.length();++j)
            {
                if(i + j >= a.length())
                    continue;
                if(a[i + j] - '0' + b[j] - '0' > 3)
                    break;
            }
            if (j == b.length())
            {
                int t = getMax(i + b.length(), a.length());
                x1 = getMin(x1,t);
            }
        }
        int x2 = a.length() + b.length();
        i = 0;
        for (; i < b.length(); ++i)
        {
            int j = 0;
            for (; j < a.length();++j)
            {
                if(i + j >= b.length())
                    continue;
                if(b[i + j] - '0' + a[j] - '0' > 3)
                    break;
            }
            if (j == a.length())
            {
                int t = getMax(i + a.length(), b.length());
                x2 = getMin(t,x2);
            }
        }

        cout << getMin(x1, x2) << endl;
    }
    return 0;
}