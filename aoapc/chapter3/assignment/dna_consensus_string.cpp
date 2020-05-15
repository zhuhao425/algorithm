#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n, m;
        cin >> m >> n;
        vector<string> instr(m, "");
        for (int i = 0; i < m;++i)
            cin >> instr[i];
        string ans;
        int diff = 0;
        for (int i = 0; i < n; ++i)
        {
            int a = 0;
            int c = 0;
            int g = 0;
            int t = 0;
            for (int j = 0; j < m;++j)
            {
                if(instr[j][i] == 'A')
                    ++a;
                else if(instr[j][i] == 'C')
                    ++c;
                else if(instr[j][i] == 'G')
                    ++g;
                else if(instr[j][i] == 'T')
                    ++t;
            }
            int tot = a + c + g + t;
            if (a >= c && a >= g && a >= t)
            {
                diff += tot - a;
                ans += 'A';
            }
            else if(c >= a && c >= g && c >= t)
            {
                diff += tot - c;
                ans += 'C';
            }
            else if(g >= a && g >= c && g >= t)
            {
                diff += tot - g;
                ans += 'G';
            }
            else if(t >= a && t >= c && t >= g)
            {
                diff += tot - t;
                ans += 'T';
            }
        }
        cout << ans << endl;
        cout << diff << endl;
    }
    return 0;
}