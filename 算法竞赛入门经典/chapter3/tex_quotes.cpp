#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string x;
    int count = 0;
    while (getline(cin, x))
    {
        string ans;
        for (int i = 0; i < x.length(); ++i)
        {
            if(x[i] != '\"')
            {
                ans += x[i];
                continue;
            }
            count = !count;
            if (count % 2 == 1)
                ans += "``";
            else
                ans += "''";
        }
        cout << ans << endl;
    }
    return 0;
}