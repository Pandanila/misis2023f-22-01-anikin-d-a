#include<iostream>
using namespace std;
char c[10002];
long i,j,k[1000];
 
int main()
{
 cin>>c;
 for(i=0;c[i];i++)
  k[c[i]]=1;
 for(i=0;i<300;i++)
  j+=k[i];
 cout<<(j%2==1?"IGNORE HIM!": "CHAT WITH HER!");
}
