#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Playfair {
public:
	Playfair(string password);
	void print_key(void);
	string encrypt(string plain_text);	

private:
	pair<int, int> index_of(char c);
	vector<vector<char>> key_matrix;
};

Playfair::Playfair(string password) : key_matrix(vector<vector<char>>(5, vector<char>(5)))
{
	vector<bool> seen(25);
	int matrix_row = 0;
	int matrix_col = 0;

	for (int i = 0, L = password.length(); i < L; ++i)
	{
		int letter_index = (password[i] >= 'J') ? password[i] - 66 : password[i] - 65;
		if (seen[letter_index] == 0)
		{
			seen[letter_index] = true;
			key_matrix[matrix_row][matrix_col] = (password[i] == 'J') ? 'I' : password[i];
			matrix_col = ++matrix_col % 5;
			if (matrix_col == 0)
			{
				++matrix_row;
			}
		}
	}

	for (int i = 0; i < 25; ++i)
	{
		if (seen[i] == 0)
		{
			key_matrix[matrix_row][matrix_col] = (i <= 8) ? i + 65 : i + 66;
			matrix_col = ++matrix_col % 5;
			if (matrix_col == 0)
			{
				++matrix_row;
			}
		}
	}
}

void Playfair::print_key(void)
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			cout << key_matrix[i][j] << " ";
		}
		cout << endl;
	}
}

string Playfair::encrypt(string plain_text) 
{
	for (int i = 0; i < plain_text.length(); i+=2)
	{
		if (plain_text[i] == 'J')
		{
			plain_text[i] = 'I';
		}
		if (i + 1 != plain_text.length() && plain_text[i+1] == 'J')
		{
			plain_text[i+1] = 'I';
		}
		if (i + 1 != plain_text.length() && plain_text[i] == plain_text[i + 1])
		{
			if (plain_text[i] == 'X')
			{
				plain_text.insert(i + 1, 1, 'Q');
			}
			else
			{
				plain_text.insert(i + 1, 1, 'X');
			}
		}
	}

	if (plain_text.length() % 2 == 1)
	{
		if (plain_text[plain_text.length()-1] == 'X')
		{
			plain_text.append(1, 'Q');
		}
		else
		{
			plain_text.append(1, 'X');
		}
	}
	cout << plain_text << endl;
	string cipher_text;
	for (int i = 0, L = plain_text.length(); i < L; i+=2)
	{
		pair<int, int> index_c1 = index_of(plain_text[i]);
		pair<int, int> index_c2 = index_of(plain_text[i+1]);

		if (index_c1.first == index_c2.first)
		{
			cipher_text.append(1, key_matrix[index_c1.first][(index_c1.second + 1) % 5]);
			cipher_text.append(1, key_matrix[index_c2.first][(index_c2.second + 1) % 5]);
		}
		else if (index_c1.second == index_c2.second)
		{
			cipher_text.append(1, key_matrix[(index_c1.first + 1) % 5][index_c1.second]);
			cipher_text.append(1, key_matrix[(index_c2.first + 1) % 5][index_c1.second]);
		}
		else
		{ 
			cipher_text.append(1, key_matrix[index_c1.first][index_c2.second]);
			cipher_text.append(1, key_matrix[index_c2.first][index_c1.second]);
		}
	}
	return cipher_text;
}

pair<int, int> Playfair::index_of(char c) 
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (key_matrix[i][j] == c)
			{
				return { i, j };
			}
		}
	}
	return { 5, 5 };
}

int main()
{
	string password;
	string plain_text;

	cin >> password;
	cin >> plain_text;

	Playfair p(password);
	p.print_key();
	cout << p.encrypt(plain_text);

	return 0;
}