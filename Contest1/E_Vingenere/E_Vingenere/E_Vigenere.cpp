#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	bool one_time_pad = false;
	string key;
	string plain_text;

	cin >> key;
	cin >> plain_text;

	int key_len = key.length();
	int plain_len = plain_text.length();

	if (key_len < plain_len)
	{
		for (int i = key_len; i < plain_len; ++i)
		{
			key.append(1, key[i-key_len]);
		}
	}
	else if (key_len == plain_len)
	{
		one_time_pad = true;
	}
	
	string vigenere_cipher_text;
	vector<unsigned int> vernam_cipher;
	for (int i = 0; i < plain_len; ++i)
	{
		vigenere_cipher_text.append(1, (((plain_text[i] - 65) + (key[i] - 65)) % 26) + 65);
		vernam_cipher.push_back(plain_text[i] ^ key[i]);
	}
	
	cout << "Vigenere: " << vigenere_cipher_text << endl;
	cout << "Vernam: ";

	cout << std::hex << std::uppercase;
	for (int i = 0; i < vernam_cipher.size(); ++i)
	{
		if (vernam_cipher[i] < 16)
		{
			cout << 0;
		}
		cout << vernam_cipher[i];
	}
	cout << endl;
	cout << "One-Time Pad: ";
	
	if (one_time_pad)
	{
		cout << "YES";
	}
	else
	{
		cout << "NO";
	}

	return 0;
}
