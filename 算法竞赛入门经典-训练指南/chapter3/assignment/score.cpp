#include <iostream>
#include <string>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        string x;
        cin >> x;
        int mark = 0;
        int count = 0;
        for (int i = 0; i < x.length(); ++i)
        {
            if(x[i] == 'X')
                mark = 0;
            else
                ++mark;
            count += mark;
        }
        cout << count << endl;
    }
    return 0;
}