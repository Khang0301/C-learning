#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string input = "bai5_6.inp";
string output = "bai5_6.oup";
unsigned long long m,n,k,mx;
unsigned long long ucntn[10000],ucntm[10000],countntn[10000],countntm[10000];
int csn,csm;

void nhap();
void tao_uoc();
void pushm(int x);
int times(int x,int snt);
int checkuntm(int x);

void nhap()
{
    ifstream f;
    f.open(input);
    f >> n >> m;
    f.close();
}

void pushm(int x)
{
    bool pushed = false;
    if (csm==0)
    {
        csm++;
        ucntm[csm] = x;
        countntm[csm]=1;
        pushed = true;
    }
    else
        for (int i=1;i<=csm;i++)
            if (x==ucntm[i])
                {
                    countntm[i]++;
                    pushed = true;
                }
    if (!pushed)
    {
        csm++;
        ucntm[csm] = x;
        countntm[csm] =1;
    }
}

int times(int x,int snt)
{
    int kq=0;
    while (x>1 && x%snt ==0)
    {
        x /= snt;
        kq++;
    }
    return kq;
}

int checkuntm(int x)
{
    int kq = -1;
    for (int i = 1;i<=csn;i++)
        if (ucntn[i]==x)
            kq = i;
    return kq;

}

void tao_uoc()
{
    int i;
    //Xay dung day ucntm va countntm
    csm = 0;
    while (m>1)
    {
        i = 2;
        while (i<=m && m%i !=0)
            i++;
        if (m%i==0 && i>1)
            {
                pushm(i);
                m /= i;
            }
    }

    //Xay dung day ucntn va countntn
    for (int i=1;i<=csm;i++)
    {
        for (int j = 2;j<=n;j++)
            if (j%ucntm[i]==0)
                if (checkuntm(ucntm[i])>0)
                    countntn[checkuntm(ucntm[i])] += times(j,ucntm[i]);
                else
                {
                    csn++;
                    ucntn[csn] = ucntm[i];
                    countntn[csn] += times(j,ucntm[i]);
                }
    }
    cout << "N:" << endl;
    for (int i =1;i<=csn;i++)
        cout << ucntn[i] << " -> " << countntn[i] << endl;
    cout << "M:" << endl;
    for (int i =1;i<=csn;i++)
        cout << ucntm[i] << " -> " << countntm[i] << endl;
}

void xuly()
{
    mx = 0;
    for (int i=1;i<=csn;i++)
        if ((countntn[i] % countntm[i] ==0) && (mx == 0 || mx > countntn[i]/countntm[i]))
            mx = countntn[i]/countntm[i];
    cout << mx;

}

void xuat()
{
    ofstream f;
    f.open(output);
    f << mx;
    f.close();
}
int main()
{
    nhap();
    tao_uoc();
    xuly();
    xuat();
}
