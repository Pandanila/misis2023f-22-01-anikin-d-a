#include<iostream>
#include<string>
using namespace std;
int n,k,i,j,a[51];
int main(){
cin>>n>>k;
while(n>i)cin>>a[i++];
while(a[j] && a[j] >= a[k-1])++j;
cout<<j;
}
