#include <unordered_set>
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int main()
{
    int n;
    while (cin >> n)
    {
        if(n == -1)
            break;
        printf("Round %d\n", n);
        string target, guess;
        cin >> target >> guess;
        unordered_set<char> st;
        unordered_set<char> wrong_guess;
        for (int i = 0; i < target.length(); ++i)
            st.insert(target[i]);
        int tag = false;
        for (int i = 0; i < guess.length(); ++i)
        {
            unordered_set<char>::iterator it = st.find(guess[i]);
            if(it == st.end())
            {
                wrong_guess.insert(guess[i]);
                if (wrong_guess.size() >= 7)
                {
                    tag = true;
                    cout << "You lose." << endl;
                    break;
                }
            }
            else
            {
                st.erase(guess[i]);
                if(st.size() == 0)
                {
                    tag = true;
                    cout << "You win." << endl;
                    break;
                }
            }
        }
        if(!tag)
            cout << "You chickened out." << endl;
    }
    return 0;
}