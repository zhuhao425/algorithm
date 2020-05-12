#include <string>
#include <iostream>

using namespace std;

int main()
{
    string s, t;
    while (cin >> s >> t)
    {
        int p = 0;
        for (int i = 0; i < t.length();++i)
        {
            if(t[i] == s[p])
                ++p;
            if(p >= s.length())
                break;
        }
        if(p >= s.length())
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}