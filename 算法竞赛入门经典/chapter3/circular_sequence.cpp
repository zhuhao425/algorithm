#include <iostream>
#include <string>
#include <cstdio>
#include <set>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        string x;
        cin >> x;
        set<string> st;
        for (int i = 0; i < x.length();++i)
        {
            string tmp = x.substr(i);
            tmp += x.substr(0,i);
            st.insert(tmp);
        }
        set<string>::iterator it = st.begin();
        cout << *it << endl;
    }
    return 0;
}