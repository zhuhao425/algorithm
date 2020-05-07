#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int n;
    while (cin >> n)
    {
        for (int i = 1; i <= n;++i)
        {
            for (int j = 0; j < i - 1;++j)
                cout << " ";
            int x = 1 + (n - i) * 2;
            while(x--)
                cout << "#";
            cout << endl;
        }
    }
    return 0;
}