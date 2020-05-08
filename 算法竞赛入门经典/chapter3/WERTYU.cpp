#include <string>
#include <iostream>

using namespace std;

int main()
{
    string mark = {"`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./"};
    string x;
    while(getline(cin,x))
    {
        for (int i = 0; i < x.length();++i)
        {
            if(x[i] == ' ')
                continue;
            for (int j = 0; j < mark.length();++j)
                if(x[i] == mark[j])
                {
                    x[i] = mark[j - 1];
                    break;
                }
        }
        cout << x << endl;
    }
    return 0;
}