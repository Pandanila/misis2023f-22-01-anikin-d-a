#include<iostream>
using namespace std;
int main()
{
	int n,sum=0;
	cin >> n;
	getchar();
	while (n--)
	{
		sum += (getchar() == 'A' ? 1 : -1);
	}
	cout << (sum == 0 ? "Friendship" : (sum > 0 ? "Anton" : "Danik"));
	return 0;
}
