#include <string>
#include <iostream>
#include <cstdio>
#include <unordered_map>

using namespace std;

void nextString(string& tmp)
{
    if(tmp == "")
    {
        tmp = "0";
        return;
    }
    int index = tmp.length() - 1;
    while (true)
    {
        if(tmp[index] == '0')
        {
            tmp[index] = '1';
            break;
        }
        else
        {
            tmp[index] = '0';
            --index;
        }
    }
    string x;
    for (int i = 0; i < tmp.length(); ++i)
        x += '1';
    if(tmp == x)
    {
        string y;
        for (int i = 0; i < tmp.length() + 1; ++i)
            y += '0';
        tmp = y;
    }
}

string getNextString(int len)
{
    string ans;
    while(len > 0)
    {
        char c = getchar();
        if (c == '0' || c == '1')
        {
            ans += c;
            --len;
        }
    }
    return ans;
}

int main()
{
    string header;
    while (getline(cin, header))
    {
        if(header.length() == 0)
            continue;
        unordered_map<string, char> mp;
        string tmp;
        for (int i = 0; i < header.length(); ++i)
        {
            nextString(tmp);
            mp.insert(make_pair(tmp, header[i]));
        }
        string ans;
        while (true)
        {
            string x = getNextString(3);
            if(x == "000")
                break;
            int len = (x[0] - '0') * 4 + (x[1] - '0') * 2 + x[2] - '0';
            string terminalString;
            for (int i = 0; i < len;++i)
                terminalString += '1';
            while (true)
            {
                string y = getNextString(len);
                if(y ==  terminalString)
                    break;
                unordered_map<string, char>::iterator it = mp.find(y);
                ans += it->second;
            }
        }
        cout << ans << endl;
    }
    return 0;
}