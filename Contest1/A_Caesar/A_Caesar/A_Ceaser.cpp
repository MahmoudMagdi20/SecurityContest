#include <iostream>

using namespace std;

int main(void)
{
	long long key;
	cin >> key;

	string plain_text;
	cin >> plain_text;

	string cipher_text;
	for (int i = 0; i < plain_text.length(); ++i)
	{
		cipher_text.append(1, (((plain_text[i] - 65) + key) % 26) + 65);
	}

	cout << cipher_text;
	return 0;
}