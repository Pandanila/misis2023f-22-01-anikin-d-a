#include<iostream>
#include<string>
using namespace std;
 
int main(){
    string s,t;
    cin>>s>>t;
    reverse(s.begin(),s.end());
    cout<<(s==t ? "YES" : "NO");
}
