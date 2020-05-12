#include <string>
#include <iostream>
#include <vector>

using namespace std;

int step[][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int main()
{
    vector<string> puzzle(5,"");
    int t = 1;
    while (true)
    {
        getline(cin, puzzle[0]);
        if(puzzle[0].length() == 1 && puzzle[0][0] == 'Z')
            break;
        if(puzzle[0].length() == 0)
            continue;
        for (int i = 1; i < 5; ++i)
        {
            getline(cin,puzzle[i]);
            if(puzzle[i].length() < 5)
                puzzle[i].push_back(' ');
        }
        int blackx = 0;
        int blacky = 0;
        for (int i = 0; i < 5;++i)
            for (int j = 0; j < 5;++j)
                if(puzzle[i][j] == ' ')
                {
                    blackx = i;
                    blacky = j;
                    break;
                }
        int tag = true;
        if(t != 1)
            cout << endl;
        printf("Puzzle #%d:\n", t++);
        while (true)
        {
            char c = getchar();
            int st = -1;
            if (c == 'A')
                st = 0;
            else if (c == 'B')
                st = 1;
            else if (c == 'L')
                st = 2;
            else if (c == 'R')
                st = 3;
            else if (c == '0')
                break;
            if(!tag)
                continue;
            if (st != -1)
            {
                int nextx = blackx + step[st][0];
                int nexty = blacky + step[st][1];
                if(nextx < 0 || nextx >= 5)
                {
                    tag = false;
                    continue;
                }
                if (nexty < 0 || nexty >= 5)
                {
                    tag = false;
                    continue;
                }
                puzzle[blackx][blacky] = puzzle[nextx][nexty];
                puzzle[nextx][nexty] = ' ';
                blackx = nextx;
                blacky = nexty;
            }
        }
        if(tag)
            for (int i = 0; i < 5;++i)
            {
                cout << puzzle[i][0];
                for (int j = 1; j < 5;++j)
                    //if(j != 4 || (j == 4 && puzzle[i][j] != ' '))
                        cout << " " << puzzle[i][j];
                cout << endl;
            }
        else
            cout << "This puzzle has no final configuration." << endl;
    }
    return 0;
}