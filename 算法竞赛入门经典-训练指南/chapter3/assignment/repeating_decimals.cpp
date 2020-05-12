#include <string>
#include <iostream>
#include <unordered_map>
#include <cstdio>

using namespace std;

int main()
{
    int a, b;
    int t = 1;
    while (cin >> a >> b)
    {
        int real = a / b;
        int least = a % b;
        unordered_map<int, int> mp;
        int index = 1;
        int start = -1, end = -1;
        string ans;
        while (true)
        {
            int now = least;
            unordered_map<int, int>::iterator it = mp.find(now);
            if(it != mp.end())
            {
                start = it->second;
                end = index;
                break;
            }
            least *= 10;
            int nowf = least / b;
            least = least % b;
            ans += (nowf + '0');
            mp.insert(make_pair(now, index));
            ++index;
        }
        if(ans.length() > 50)
        {
            ans = ans.substr(0,50);
            ans += "...";
        }
        int tot = end - start;
        if (start >= 50)
            start = 50;
        if(end >= 50)
            end = 53;
        ans = ans.substr(0, start - 1) + "(" + ans.substr(start - 1) + ")";
        //if(t != 1)
            //puts("");
        printf("%d/%d = %d.", a, b, real);
        cout << ans << endl;
        printf("   %d = number of digits in repeating cycle\n\n",tot);
        ++t;
    }
    return 0;
}