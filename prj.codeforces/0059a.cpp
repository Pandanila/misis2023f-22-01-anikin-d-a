#include<iostream>
using namespace std;
int main()
{
    char x[101];
    cin>>x;
    int i,a=0,b=0;
    for(i=0;i<strlen(x);i++)
    {
        if(x[i]>90) a++;
        else b++;
    }
    if(a>=b) strlwr(x);
    else strupr(x);
    cout<<x;
    return 0;
}
