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
        int x1;
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
                x1 = getMax(i + b.length(), a.length());
                break;
            }
        }
        if(i == a.length())
            x1 = a.length() + b.length();

        int x2;
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
                x2 = getMax(i + a.length(), b.length());
                break;
            }
        }
        if(i == b.length())
            x2 = a.length() + b.length();

        cout << getMin(x1, x2) << endl;
    }
    return 0;
}