#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int r, c;
    int t = 1;
    while (cin >> r)
    {
        if(r == 0)
            break;
        cin >> c;
        vector<string> x(r, "");
        for (int i = 0; i < r; ++i)
            cin >> x[i];
        if(t != 1)
            puts("");
        printf("puzzle #%d:\n", t++);
        printf("Across\n");
        vector<string> across;
        vector<int> acrossNum;
        vector<vector<int>> aserial;
        int asindex = 0;
        for (int i = 0; i < r; ++i)
        {
            vector<int> astmp;
            for (int j = 0; j < c; ++j)
            {
                if(x[i][j] == '*')
                {
                    astmp.push_back(asindex);
                    continue;
                }
                if (j == 0 || i == 0)
                    ++asindex;
                else if(x[i - 1][j] == '*' || x[i][j - 1] == '*')
                    ++asindex;
                astmp.push_back(asindex);
            }
            aserial.push_back(astmp);
        }
        for (int i = 0; i < r; ++i)
        {
            string tmp;
            int index = 0;
            while (index < x[i].length())
            {
                if (x[i][index] == '*')
                {
                    ++index;
                    continue;
                }
                int end = index;
                while (end < x[i].length() && x[i][end] != '*')
                    ++end;
                string ans = x[i].substr(index, end - index);
                across.push_back(ans);
                acrossNum.push_back(aserial[i][index]);
                index = end;
            }
        }
        for (int i = 0; i < across.size();++i)
        {
            printf("%3d.", acrossNum[i]);
            cout << across[i] << endl;
        }
        printf("Down\n");
        vector<int> index(c,0);
        vector<string> down;
        vector<int> downNum;
        for (int i = 0; i < r; ++i)
        {
            for (int j = 0; j < c;++j)
            {
                if(i < index[j])
                    continue;
                if(x[i][j] == '*')
                    continue;
                int end = i;
                string tmps;
                while (end < r && x[end][j] != '*')
                    tmps += x[end++][j];
                if(tmps.length() > 0)
                {
                    down.push_back(tmps);
                    downNum.push_back(aserial[i][j]);
                }
                index[j] = end + 1;
            }
        }
            for (int i = 0; i < down.size(); ++i)
            {
                printf("%3d.", downNum[i]);
                cout << down[i] << endl;
            }
    }
    return 0;
}