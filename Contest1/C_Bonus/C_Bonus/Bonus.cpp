#include <iostream>
#include <vector>
#include <bits/stdc++.h> 

using namespace std;

class Playfair {
public:
	Playfair() : key_matrix(vector<vector<char>>(3, vector<char>(3))) {}
	void set_key_matrix(string key);
	string encrypt(string plain_text);

private:
	pair<int, int> index_of(char c);
	vector<vector<char>> key_matrix;
};

void Playfair::set_key_matrix(string key) 
{
	int matrix_row = 0;
	int matrix_col = 0;

	for (int i = 0; i < 9; ++i)
	{
		key_matrix[matrix_row][matrix_col] = key[i];
		matrix_col = ++matrix_col % 3;
		if (matrix_col == 0)
		{
			++matrix_row;
		}
	}
}

void permute(string str, string out, Playfair &p, string &plain_text, string &cipher_text, vector<string> &keys)
{
	// When size of str becomes 0, out has a 
	// permutation (length of out is n) 
	if (str.size() == 0)
	{
		//cout << out << endl;
		p.set_key_matrix(out);
		string c = p.encrypt(plain_text);
		if (cipher_text.compare(c) == 0)
		{
			keys.push_back(out);
		}
		return;
	}

	// One be one move all characters at 
	// the beginning of out (or result) 
	for (int i = 0; i < str.size(); i++)
	{
		// Remove first character from str and 
		// add it to out 
		permute(str.substr(1), out + str[0], p, plain_text, cipher_text, keys);

		// Rotate string in a way second character 
		// moves to the beginning. 
		rotate(str.begin(), str.begin() + 1, str.end());
	}
}

int main(void)
{
	Playfair p;
	string plain_text, cipher_text;
	vector<string> keys;
	string key = "ABCDEFGHI";

	cin >> plain_text >> cipher_text;
	permute(key, "", p, plain_text, cipher_text, keys);

	string min_key = keys[0];
	while (keys.empty() != 0)
	{
		string k = keys.back();
		keys.pop_back();
		if (min_key.compare(k) > 0)
		{
			min_key = k;
		}
	}

	cout << min_key;
	return 0;
}


string Playfair::encrypt(string plain_text)
{
	for (int i = 0; i < plain_text.length(); i += 2)
	{
		if (plain_text[i] == 'J')
		{
			plain_text[i] = 'I';
		}
		if (i + 1 != plain_text.length() && plain_text[i + 1] == 'J')
		{
			plain_text[i + 1] = 'I';
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
		if (plain_text[plain_text.length() - 1] == 'X')
		{
			plain_text.append(1, 'Q');
		}
		else
		{
			plain_text.append(1, 'X');
		}
	}
	
	string cipher_text;
	for (int i = 0, L = plain_text.length(); i < L; i += 2)
	{
		pair<int, int> index_c1 = index_of(plain_text[i]);
		pair<int, int> index_c2 = index_of(plain_text[i + 1]);

		if (index_c1.first == index_c2.first)
		{
			cipher_text.append(1, key_matrix[index_c1.first][(index_c1.second + 1) % 3]);
			cipher_text.append(1, key_matrix[index_c2.first][(index_c2.second + 1) % 3]);
		}
		else if (index_c1.second == index_c2.second)
		{
			cipher_text.append(1, key_matrix[(index_c1.first + 1) % 3][index_c1.second]);
			cipher_text.append(1, key_matrix[(index_c2.first + 1) % 3][index_c1.second]);
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
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (key_matrix[i][j] == c)
			{
				return { i, j };
			}
		}
	}
	return { 3, 3 };
}