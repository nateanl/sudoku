#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

int question[10][10]{};
int rowmark[10][10]{};
int colmark[10][10]{};
int blockmark[10][10]{};
int row[10]{},col[10]{},block[10]{};

clock_t start,finish;
class point
{
public:
    int r,c,n=0;
    point(){};
    point(int _r, int _c,int _n=0)
    {
        r=_r;
        c=_c;
        n=_n;
    }
    point(const point &p)
    {
        r=p.r;
        c=p.c;
        n=p.n;
    }
};
vector<point>tofill;
bool judge(int r,int c,int n);
bool dfs(int);
void setmark(int r, int c, int n, bool flag);
inline int getblocknum(int r,int c);
void printboard();
void Clear();
int main(int argc, const char * argv[]) {
    
    int count;
    cin>>count;
    
    while(count--)
    {
        for(int r=1;r<10;r++)//from 1 to 9
        {
            for(int c=1;c<10;c++)//from 1 to 9
            {
                char ch;
                cin>>ch;
                question[r][c]=ch-'0';
                if(question[r][c]==0)
                {
                    tofill.push_back(point(r,c));
                }
                else
                {
                    setmark(r, c, question[r][c], 1);
                    row[r]++;
                    col[c]++;
                    block[getblocknum(r, c)]++;
                }
            }
        }
        start=clock();
#if 1
        for(int i=0;i<tofill.size();i++)
        {
            int r=tofill[i].r,c=tofill[i].c;
            tofill[i].n=row[r]+col[c]+block[getblocknum(r, c)];
        }
        for(int i=0;i<tofill.size();i++)
        {
            int m=i;
            for(int j=i;j<tofill.size()-1;j++)
            {
                
                if(tofill[m].n<tofill[j+1].n)
                    m=j+1;
            }
            swap(tofill[i],tofill[m]);
        }
#endif
        if(dfs(0))
        {
            printboard();
        }
        Clear();
    }
    finish=clock();
    //cout<<(finish-start)<<endl;
    return 0;
    
}
void setmark(int r, int c, int n, bool flag)
{
    rowmark[r][n]=flag;
    colmark[c][n]=flag;
    blockmark[getblocknum(r, c)][n]=flag;
}

inline int getblocknum(int r,int c)
{
    return ((r-1)/3)*3+((c-1)/3);
}

bool judge(int r,int c,int n)
{
    return !rowmark[r][n]&&!colmark[c][n]&&!blockmark[getblocknum(r, c)][n];
}

void printboard()
{
    for(int r=1;r<10;r++)//from 1 to 9
    {
        for(int c=1;c<10;c++)//from 1 to 9
        {
            cout<<question[r][c];
        }
        cout<<endl;
    }
}
void Clear()
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            rowmark[i][j]=0;
            colmark[i][j]=0;
            blockmark[i][j]=0;
            question[i][j]=0;
        }
        row[i]=0;
        col[i]=0;
        block[i]=0;
    }
    tofill.clear();
    vector<point>().swap(tofill);
}

bool dfs(int step)
{
    if(step==tofill.size())
    {
        return true;
    }
#if 0
    int reverse=(int)tofill.size()-step-1;
    int r=tofill[reverse].r,c=tofill[reverse].c;
#else
    int r=tofill[step].r,c=tofill[step].c;
#endif
    for(int i=1;i<10;i++)
    {
        if(judge(r, c, i))
        {
            question[r][c]=i;
            setmark(r, c, question[r][c], 1);
            if(dfs(step+1))return true;
            setmark(r, c, question[r][c], 0);
            question[r][c]=0;
        }
    }
    return false;
}