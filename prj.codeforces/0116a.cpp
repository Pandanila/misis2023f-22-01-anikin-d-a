#include<iostream>
using namespace std;
 
int main(){
	int n,i,max=0,a,b,temp=0;
	cin>>n;
	for(i=0;i<n-1;i++){
		cin>>a>>b;
		temp+=b-a;
		if(temp>max)max=temp;
	}
	cout<<max;
}
