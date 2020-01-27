#include <iostream>

using namespace std;

bool flag = false;

long long ext_euclid(long long q, long long a1, long long a2, long long a3, long long b1, long long b2, long long b3)
{
	if (b3 == 1)
	{
		return b2;
	}
	else if (b3 == 0)
	{
		flag = true;
		return 0;
	}
	q = a3 / b3;
	return ext_euclid(q, b1, b2, b3, a1 - q * b1, a2 - q * b2, a3 % b3);
}

long long mul_inv(long long a3, long long b3)
{
	return ext_euclid(0, 1, 0, a3, 0, 1, b3);
}

int main()
{
	long long a, b;
	cin >> a >> b;

	long long m = mul_inv(a, b);

	if (flag == true)
	{
		cout << "IMPOSSIBLE";
	}
	else
	{
		if (m < 0)
		{
			m = m + a;
		}
		if (b > a)
		{
			b = b % a;
		}
		while (b < 0)
		{
			b += a;
		}
		cout << a - b << " " << m;
	}

	return 0;
}