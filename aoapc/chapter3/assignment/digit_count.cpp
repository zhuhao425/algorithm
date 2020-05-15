#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        int n;
        cin >> n;
        vector<int> count(10,0);
        for (int i = 1; i <= n; ++i)
        {
            string x = to_string(i);
            for (int j = 0; j < x.length();++j)
                ++count[x[j] - '0'];
        }
        cout << count[0];
        for (int i = 1; i < 10;++i)
            cout << " " << count[i];
        cout << endl;
    }
    return 0;
}