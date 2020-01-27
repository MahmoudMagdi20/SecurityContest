#include <iostream>

using namespace std;

long long gcd(int a, int b)
{
	if (b == 0)
	{
		return a;
	}

	int r = a % b;
	a = b;
	b = r;
	gcd(a, b);
}

int main()
{
	int a, b;
	cin >> a >> b;

	cout << gcd(a, b);
	return 0;
}