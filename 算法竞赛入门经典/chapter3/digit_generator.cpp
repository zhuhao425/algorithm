#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>


using namespace std;

int main()
{
    int T;
    cin >> T;
    unordered_map<int, int> mp;
    for (int i = 1; i <= 100000; ++i)
    {
        string x = to_string(i);
        int tmp = i;
        for (int j = 0; j < x.length(); ++j)
            tmp += x[j] - '0';
        unordered_map<int, int>::iterator it = mp.find(tmp);
        if(it == mp.end())
            mp.insert(make_pair(tmp,i));
    }
    while(T--)
    {
        int n;
        cin >> n;
        unordered_map<int, int>::iterator it = mp.find(n);
        if(it == mp.end())
            cout << 0 << endl;
        else
            cout << it->second << endl;
    }
    return 0;
}