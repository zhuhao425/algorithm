#include <string>
#include <iostream>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        string x;
        cin >> x;
        for (int len = 1; len <= x.length();++len)
        {
            string subx = x.substr(0,len);
            int mark;
            for (mark = 0; mark < x.length();mark +=len)
            {
                if(subx != x.substr(mark,len))
                    break;
            }
            if(mark == x.length())
            {
                cout << len << endl;
                break;
            }
        }
        if (T > 0)
            cout << endl;
    }
    return 0;
}