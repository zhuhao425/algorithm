#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

char mark[] = {'A',' ',' ',' ','3'};

bool checkMirrored(const string& x)
{
    int l = 0;
    int r = x.length() - 1;
    while(l <= r)
    {
        if(x[l] == 'A' && x[r] != 'A')
            return false;
        if (x[l] == 'E' && x[r] != '3')
            return false;
        if(x[l] == 'H' && x[r] != 'H')
            return false;
        if(x[l] == 'I' && x[r] != 'I')
            return false;
        if(x[l] == 'J' && x[r] != 'L')
            return false;
        if(x[l] == 'L' && x[r] != 'J')
            return false;
        if(x[l] == 'M' && x[r] != 'M')
            return false;
        if(x[l] == 'O' && x[r] != 'O')
            return false;
        if(x[l] == 'S' && x[r] != '2')
            return false;
        if(x[l] == 'T' && x[r] != 'T')
            return false;
        if(x[l] == 'U' && x[r] != 'U')
            return false;
        if(x[l] == 'V' && x[r] != 'V')
            return false;
        if(x[l] == 'W' && x[r] != 'W')
            return false;
        if(x[l] == 'X' && x[r] != 'X')
            return false;
        if(x[l] == 'Y' && x[r] != 'Y')
            return false;
        if(x[l] == 'Z' && x[r] != '5')
            return false;
        if(x[l] == '1' && x[r] != '1')
            return false;
        if(x[l] == '2' && x[r] != 'S')
            return false;
        if(x[l] == '3' && x[r] != 'E')
            return false;
        if(x[l] == '5' && x[r] != 'Z')
            return false;
        if(x[l] == '8' && x[r] != '8')
            return false;
        if(x[l] == 'B' || x[l] == 'C' || x[l] == 'D' || x[l] == 'F' || x[l] == 'G' || x[l] == 'K' || x[l] == 'N' || x[l] == 'P' || x[l] == 'Q' || x[l] == 'R' || x[l] == '4' || x[l] == '6' || x[l] == '7' || x[l] == '9')
            return false;
        ++l;
        --r;
    }
    return true;
}

bool checkPalind(const string& x)
{
    int l = 0;
    int r = x.length() - 1;
    while(l < r)
    {
        if(x[l] != x[r])
            return false;
        ++l;
        --r;
    }
    return true;
}

int main()
{
    string x;
    while (cin >> x)
    {
        bool ismirrored = checkMirrored(x);
        bool isPalind = checkPalind(x);
        cout << x << " -- ";
        if(ismirrored && isPalind)
            cout << "is a mirrored palindrome." << endl;
        else if(ismirrored && !isPalind)
            cout << "is a mirrored string." << endl;
        else if(!ismirrored && isPalind)
            cout << "is a regular palindrome." << endl;
        else
            cout << "is not a palindrome." << endl;
        cout << endl;
    }
    return 0;
}