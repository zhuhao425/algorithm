#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>

using namespace std;

void collectInfo(map<pair<int,int>,pair<int,int>>& mp,vector<vector<pair<int,int>>>& data,int vn,int vm)
{
    for (int i = 0; i < vn;++i)
        for (int j = 0; j < vm;++j)
            if(data[i][j] != make_pair(-1,-1))
                mp.insert(make_pair(data[i][j], make_pair(i + 1, j + 1)));
}

void opEX(vector<vector<pair<int,int>>>& data)
{
    int x1, x2, y1, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    swap(data[x1 - 1][y1 - 1], data[x2 - 1][y2 - 1]);
}
//r是横着的，c是竖着的
void opDC(vector<vector<pair<int,int>>>& data,int& vn,int& vm)
{
    vector<bool> mark(vm,false);
    int n;
    cin >> n;
    while(n--)
    {
        int index;
        cin >> index;
        mark[index - 1] = true;
    }
    int now = 0;
    int next = 0;
    while(next < vm)
    {
        if(!mark[next])
        {
            for (int i = 0; i < vn;++i)
                data[i][now] = data[i][next];
            ++now;
        }
        ++next;
    }
    vm = now;
}

void opDR(vector<vector<pair<int,int>>>& data,int& vn,int& vm)
{
    vector<bool> mark(vn,false);
    int n;
    cin >> n;
    while(n--)
    {
        int index;
        cin >> index;
        mark[index - 1] = true;
    }
    int now = 0;
    int next = 0;
    while(next < vn)
    {
        if(!mark[next])
        {
            for (int i = 0; i < vm;++i)
                data[now][i] = data[next][i];
            ++now;
        }
        ++next;
    }
    vn = now;
}

void opIC(vector<vector<pair<int,int>>>& data,int& vn,int& vm)
{
    int n;
    cin >> n;
    vector<bool> mark(vm,false);
    int now = vm + n - 1;
    int t = now;
    while (n--)
    {
        int index;
        cin >> index;
        mark[index - 1] = true;
    }
    int index = vm - 1;
    while(index >= 0)
    {
        for (int i = 0; i < vn;++i)
        {
            data[i][now] = data[i][index];
        }
        --now;
        if(mark[index])
        {
            for (int i = 0; i < vn;++i)
            {
                data[i][now] = make_pair(-1,-1);
            }
            --now;
        }
        --index;
    }
    vm = t + 1;
}

void opIR(vector<vector<pair<int,int>>>& data,int& vn,int& vm)
{
    int n;
    cin >> n;
    vector<bool> mark(vn,false);
    int now = vn + n - 1;
    int t = now;
    while (n--)
    {
        int index;
        cin >> index;
        mark[index - 1] = true;
    }
    int index = vn - 1;
    while(index >= 0)
    {
        for (int i = 0; i < vm;++i)
        {
            data[now][i] = data[index][i];
        }
        --now;
        if(mark[index])
        {
            for (int i = 0; i < vm;++i)
            {
                data[now][i] = make_pair(-1,-1);
            }
            --now;
        }
        --index;
    }
    vn = t + 1;
}


void processOperate(vector<vector<pair<int,int>>>& data,int& vn,int& vm)
{
    int n;
    cin >> n;
    while(n--)
    {
        string op;
        do{
            cin >> op;
        } while (op.length() == 0);
        if(op == "EX")
            opEX(data);
        else if(op == "DC")
            opDC(data,vn,vm);
        else if(op == "DR")
            opDR(data,vn,vm);
        else if(op == "IC")
            opIC(data,vn,vm);
        else if(op == "IR")
            opIR(data,vn,vm);
    }
}

void processQuery(map<pair<int,int>,pair<int,int>>& mp)
{
    int n;
    cin >> n;
    while(n--)
    {
        int x, y;
        cin >> x >> y;
        map<pair<int, int>, pair<int, int>>::iterator it = mp.find(make_pair(x,y));
        if(it != mp.end())
            printf("Cell data in (%d,%d) moved to (%d,%d)\n",x,y,it->second.first,it->second.second);
        else
            printf("Cell data in (%d,%d) GONE\n",x,y);
    }
}

int main()
{
    int vn, vm;
    int t = 1;
    while (cin >> vn >> vm)
    {
        if(vn ==0 && vm == 0)
            break;
        vector<vector<pair<int, int>>> data;
        for (int i = 0; i < 120;++i)
        {
            vector<pair<int, int>> tmp;
            for (int j = 0; j < 120;++j)
                tmp.push_back(make_pair(i + 1,j + 1));
            data.push_back(tmp);
        }
        if(t != 1)
            puts("");
        printf("Spreadsheet #%d\n",t++);
        processOperate(data, vn, vm);
        map<pair<int, int>, pair<int, int>> mp;
        collectInfo(mp,data,vn,vm);
        processQuery(mp);
    }
    return 0;
}