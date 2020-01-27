#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

string encrypt(string plain_text, const vector<vector<long long>>& key_matrix);
string encrypt_part(const string& plain_text, const vector<vector<long long>>& mat);

int main()
{
	int key_length;
	cin >> key_length;
	
	int key_dim = sqrt(key_length);
	vector<vector<long long>> key_matrix(vector<vector<long long>>(key_dim, vector<long long>(key_dim)));
	
	for (int i = 0; i < key_dim; ++i)
	{
		for (int j = 0; j < key_dim; ++j)
		{
			long long key_entry;
			cin >> key_entry;
			key_matrix[i][j] = key_entry;
		}
	}

	string plain_text;
	cin >> plain_text;


	cout << encrypt(plain_text, key_matrix);
}

string encrypt(string plain_text, const vector<vector<long long>> &key_matrix)
{	
	int key_dim = key_matrix.size();
	if (int remainder = plain_text.length() % key_dim)
	{
		int no_of_repeated_X = key_dim - remainder;
		plain_text.append(no_of_repeated_X, 'X');
	}

	

	string cipher_text;
	for (int i = 0, L = plain_text.size(); i < L; i += key_dim)
	{
		cipher_text.append(encrypt_part(plain_text.substr(i, key_dim), key_matrix));
	}
	return cipher_text;
}

string encrypt_part(const string& plain_text, const vector<vector<long long>>& mat)
{
	vector<long long> plain_vec;

	for (int i = 0, L = plain_text.length(); i < L; ++i)
	{
		plain_vec.push_back(plain_text[i] - 65);
	}

	vector<long long> cipher_vec(plain_vec.size(), 0);
	for (int mat_row = 0; mat_row < mat.size(); ++mat_row)
	{
		for (int mat_col = 0; mat_col < mat[mat_row].size(); ++mat_col)
		{
			cipher_vec[mat_row] += mat[mat_row][mat_col] * plain_vec[mat_col];
		}
	}

	string cipher_text;
	for (int i = 0, L = cipher_vec.size(); i < L; ++i)
	{
		cipher_text.append(1, (cipher_vec[i] % 26) + 65);
	}

	return cipher_text;
}

