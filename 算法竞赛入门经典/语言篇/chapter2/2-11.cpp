#include <cstdio>
#include <iostream>

using namespace std;

#define INF 1000000000

int main()
{
    FILE *fin, *fout;
    fin = fopen("data.in","rb");
    fout = fopen("data.out","wb");
    int x, n = 0, min = INF, max = -INF, s = 0;
    while(~scanf("%d",&x))
    {
        s += x;
        if(x < min)
            min = x;
        if(x > max)
            max = x;
        ++n;
    }
    fprintf(fout, "%d %d %.3f\n", min, max, (double)s / n);
    fclose(fin);
    fclose(fout);
    return 0;
}