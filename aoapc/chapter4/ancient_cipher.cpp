#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    string a, b;
    while (cin >> a)
    {
        cin >> b;
        vector<int> va(52,0);
        vector<int> vb(52,0);
        for (int i = 0; i < a.length();++i)
        {
            if(a[i] >= 'a' && a[i] <= 'z')
                ++va[a[i] - 'a'];
            else
                ++va[a[i] - 'A' + 26];
        }
        for (int i = 0; i < b.length();++i)
        {
            if(b[i] >= 'a' && b[i] <= 'z')
                ++vb[b[i] - 'a'];
            else
                ++vb[b[i] - 'A' + 26];
        }
        sort(va.begin(),va.end());
        sort(vb.begin(),vb.end());
        int tag = true;
        for (int i = 0; i < 52; ++i)
            if(va[i] != vb[i])
            {
                tag = false;
                break;
            }
        if(tag)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}