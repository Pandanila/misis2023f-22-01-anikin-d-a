#include<iostream>
int main(){
int n,p=0,a,b,c;
std::cin>>n;
while(std::cin>>a>>b>>c){
p+=(a+b+c>=2);
}
std::cout<<p;
}
