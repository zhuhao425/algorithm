#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    if(!(a + b > c && a + c > b && b + c > a))
        cout << "not a triangle" << endl;
    else
    {
        if(a > b && a > c)
            if(a * a == b * b + c * c)
                cout << "yes" << endl;
            else
                cout << "no" << endl;
        else if(b > a && b > c)
            if(b * b == a * a + c * c)
                cout << "yes" << endl;
            else
                cout << "no" << endl;
        else if(c > b && c > a)
            if(c * c == b * b + a * a)
                cout << "yes" << endl;
            else
                cout << "no" << endl;
        else
            cout << "no" << endl;
    }
    return 0;
}