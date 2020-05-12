#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int main()
{
    string x;
    while (cin >> x)
    {
        int e;
        for (e = 0; e < x.length();++e)
            if(x[e] == 'e')
                break;
        int right = stoi(x.substr(e + 1));
        string left = x.substr(0,e);
        if(left.length() == 1 && left[0] == '0' && right == 0)
            break;

        left[1] = left[0];
        left[0] = '.';
        ++right;

        cout << left << " " << right << endl;
    }
    return 0;
}