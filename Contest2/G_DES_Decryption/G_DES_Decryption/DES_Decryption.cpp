#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <stack>
#include <array>

using namespace std;

class BinaryNumber {
public:
	BinaryNumber() : binary_number("") {}

	BinaryNumber(const string& s)
	{
		binary_number = s;
	}

	BinaryNumber(unsigned long long number)
	{
		while (number > 0)
		{
			binary_number.insert(0, 1, number % 2 + '0');
			number /= 2;
		}

		if (binary_number.size() == 0)
		{
			binary_number.insert(0, 1, '0');
		}

		while (binary_number.size() % 4 != 0)
		{
			binary_number.insert(0, 1, '0');
		}
	}

	operator string() const
	{
		return binary_number;
	}

	operator unsigned long long() const
	{
		unsigned long long number = 0;
		for (int i = binary_number.size() - 1; i >= 0; --i)
		{
			number += (binary_number[i] - '0') * pow(2, binary_number.size() - i - 1);
		}
		return number;
	}

	char& operator[](size_t i)
	{
		return binary_number[i];
	}

	const char& operator[](size_t i) const
	{
		return binary_number[i];
	}

	BinaryNumber& append(BinaryNumber bits)
	{
		binary_number.append(bits);
		return *this;
	}

	BinaryNumber subset(size_t bit_num, size_t len) const
	{
		BinaryNumber out;
		for (int i = bit_num; len > 0; ++i, --len)
		{
			string c;
			c += binary_number[i - 1];
			out.append(c);
		}
		return out;
	}

	size_t size() const
	{
		return binary_number.size();
	}

	BinaryNumber operator^(const BinaryNumber& rhs) const
	{
		BinaryNumber result;
		for (size_t i = 0; i < rhs.size(); ++i)
		{
			if ((*this)[i] == rhs[i])
			{
				result.append(static_cast<string>("0"));
			}
			else
			{
				result.append(static_cast<string>("1"));
			}
		}
		return result;
	}

	BinaryNumber operator|(const BinaryNumber& rhs) const
	{
		BinaryNumber result;
		for (size_t i = 0; i < rhs.size(); ++i)
		{
			if ((*this)[i] == '0' && rhs[i] == '0')
			{
				result.append(static_cast<string>("0"));
			}
			else
			{
				result.append(static_cast<string>("1"));
			}
		}
		return result;
	}

	BinaryNumber operator<<(size_t rhs)
	{
		BinaryNumber result;
		size_t i = 0;
		for (; i < binary_number.size() - rhs; ++i)
		{
			string s;
			s += binary_number[i + rhs];
			result.append(s);
		}

		for (; i < binary_number.size(); ++i)
		{
			result.append(static_cast<string>("0"));
		}
		return result;
	}

	BinaryNumber operator>>(size_t rhs)
	{
		BinaryNumber result;
		for (size_t i = 0; i < rhs; ++i)
		{
			result.append(static_cast<string>("0"));
		}

		for (size_t i = rhs; i < binary_number.size(); ++i)
		{
			string s;
			s += binary_number[i - rhs];
			result.append(s);
		}
		return result;
	}

	BinaryNumber rotate_left(size_t rhs)
	{
		BinaryNumber temp1 = *this << rhs;
		BinaryNumber temp2 = *this >> (this->size() - rhs);
		return temp1 | temp2;
	}

private:
	string binary_number;
};

istream& operator>>(istream& is, BinaryNumber& binary_number)
{
	string s;
	is >> s;

	string bits;
	for (size_t i = 0; i < s.length(); ++i)
	{
		switch (s[i])
		{
		case '0':
			bits += "0000";
			break;
		case '1':
			bits += "0001";
			break;
		case '2':
			bits += "0010";
			break;
		case '3':
			bits += "0011";
			break;
		case '4':
			bits += "0100";
			break;
		case '5':
			bits += "0101";
			break;
		case '6':
			bits += "0110";
			break;
		case '7':
			bits += "0111";
			break;
		case '8':
			bits += "1000";
			break;
		case '9':
			bits += "1001";
			break;
		case 'A':
			bits += "1010";
			break;
		case 'B':
			bits += "1011";
			break;
		case 'C':
			bits += "1100";
			break;
		case 'D':
			bits += "1101";
			break;
		case 'E':
			bits += "1110";
			break;
		case 'F':
			bits += "1111";
			break;
		}
	}

	binary_number = bits;
	return is;
}

ostream& operator<<(ostream& os, const BinaryNumber& binary_number)
{
	string b = binary_number;
	string s;
	for (size_t i = 0; i < b.size(); i += 4)
	{
		if (b[i] == '0' && b[i + 1] == '0' &&
			b[i + 2] == '0' && b[i + 3] == '0')
		{
			s += '0';
		}
		else if (b[i] == '0' && b[i + 1] == '0' &&
			b[i + 2] == '0' && b[i + 3] == '1')
		{
			s += '1';
		}
		else if (b[i] == '0' && b[i + 1] == '0' &&
			b[i + 2] == '1' && b[i + 3] == '0')
		{
			s += '2';
		}
		else if (b[i] == '0' && b[i + 1] == '0' &&
			b[i + 2] == '1' && b[i + 3] == '1')
		{
			s += '3';
		}
		else if (b[i] == '0' && b[i + 1] == '1' &&
			b[i + 2] == '0' && b[i + 3] == '0')
		{
			s += '4';
		}
		else if (b[i] == '0' && b[i + 1] == '1' &&
			b[i + 2] == '0' && b[i + 3] == '1')
		{
			s += '5';
		}
		else if (b[i] == '0' && b[i + 1] == '1' &&
			b[i + 2] == '1' && b[i + 3] == '0')
		{
			s += '6';
		}
		else if (b[i] == '0' && b[i + 1] == '1' &&
			b[i + 2] == '1' && b[i + 3] == '1')
		{
			s += '7';
		}
		else if (b[i] == '1' && b[i + 1] == '0' &&
			b[i + 2] == '0' && b[i + 3] == '0')
		{
			s += '8';
		}
		else if (b[i] == '1' && b[i + 1] == '0' &&
			b[i + 2] == '0' && b[i + 3] == '1')
		{
			s += '9';
		}
		else if (b[i] == '1' && b[i + 1] == '0' &&
			b[i + 2] == '1' && b[i + 3] == '0')
		{
			s += 'A';
		}
		else if (b[i] == '1' && b[i + 1] == '0' &&
			b[i + 2] == '1' && b[i + 3] == '1')
		{
			s += 'B';
		}
		else if (b[i] == '1' && b[i + 1] == '1' &&
			b[i + 2] == '0' && b[i + 3] == '0')
		{
			s += 'C';
		}
		else if (b[i] == '1' && b[i + 1] == '1' &&
			b[i + 2] == '0' && b[i + 3] == '1')
		{
			s += 'D';
		}
		else if (b[i] == '1' && b[i + 1] == '1' &&
			b[i + 2] == '1' && b[i + 3] == '0')
		{
			s += 'E';
		}
		else if (b[i] == '1' && b[i + 1] == '1' &&
			b[i + 2] == '1' && b[i + 3] == '1')
		{
			s += 'F';
		}
	}

	os << s;
	return os;
}

class PermutationBox {
public:
	PermutationBox(unsigned short n) : permutation_box(n) {}
	PermutationBox(vector<unsigned short>&& v) : permutation_box(v) {}
	unsigned short& operator[](size_t i)
	{
		return permutation_box[i];
	}

	BinaryNumber output(const BinaryNumber& input)
	{
		BinaryNumber out;
		for (int i = 0; i < permutation_box.size(); ++i)
		{
			out.append(input.subset(permutation_box[i], 1));
		}
		return out;
	}

private:
	vector<unsigned short> permutation_box;
};

class SBoxUnit {
public:
	SBoxUnit(vector<vector<unsigned short>>&& il) : s_box_table(il) {}

	BinaryNumber output(const BinaryNumber& in)
	{
		BinaryNumber row = in.subset(1, 1);
		row.append(in.subset(6, 1));

		BinaryNumber col = in.subset(2, 4);

		return s_box_table[row][col];
	}
private:
	vector<vector<unsigned short>> s_box_table;
};

class SBox {
public:
	SBox(array<SBoxUnit, 8>&& il) : s_box(il) {}

	BinaryNumber output(const BinaryNumber& input)
	{
		BinaryNumber out;
		for (int i = 0; i < 8; ++i)
		{
			out.append(s_box[i].output(input.subset((i * 6) + 1, 6)));
		}
		return out;
	}
private:
	array<SBoxUnit, 8> s_box;
};

class DES_Function {
public:
	DES_Function(PermutationBox& e, SBox& sbox, PermutationBox& s) : expansion_permutation_box(e)
		, sbox(sbox)
		, straight_permutation_box(s) {}

	BinaryNumber output(const BinaryNumber& input, const BinaryNumber& key)
	{
		BinaryNumber out;
		out = expansion_permutation_box.output(input);
		out = out ^ key;
		out = sbox.output(out);
		return straight_permutation_box.output(out);
	}
private:
	PermutationBox expansion_permutation_box;
	SBox sbox;
	PermutationBox straight_permutation_box;
};

PermutationBox expansion_permutation_box({ 32,1,2,3,4,5
											 ,4,5,6,7,8,9
											 ,8,9,10,11,12,13
											 ,12,13,14,15,16,17
											 ,16,17,18,19,20,21
											 ,20,21,22,23,24,25
											 ,24,25,26,27,28,29
											 ,28,29,30,31,32,1 });
PermutationBox straight_permutation_box({ 16,7,20,21,29,12,28,17
										,1,15,23,26,5,18,31,10
										,2,8,24,14,32,27,3,9
										,19,13,30,6,22,11,4,25 });
SBoxUnit s1({
	{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
	{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
	{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
	{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
	});
SBoxUnit s2({
	{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
	{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
	{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
	{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
	});
SBoxUnit s3({
	{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
	{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
	{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
	{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
	});
SBoxUnit s4({
	{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
	{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
	{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
	{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
	});
SBoxUnit s5({
	{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
	{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
	{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
	{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
	});
SBoxUnit s6({
	{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
	{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
	{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
	{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
	});
SBoxUnit s7({
	{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
	{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
	{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
	{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
	});
SBoxUnit s8({
	{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
	{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
	{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
	{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11},
	});
SBox sbox({ s1,s2,s3,s4,s5,s6,s7,s8 });
DES_Function des_function(expansion_permutation_box, sbox, straight_permutation_box);

PermutationBox PC1({ 57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35,
										   27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4 });
PermutationBox PC2({ 14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41,
					 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32 });
array<unsigned short, 16> Rotations = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
array<BinaryNumber, 16> K;

PermutationBox IP({ 58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
					57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53, 45, 37, 29, 21, 13, 5,63, 55, 47, 39, 31, 23, 15, 7 });
PermutationBox IP_Inv({ 40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,
						60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25 });

void key_generation(BinaryNumber key_64)
{
	BinaryNumber key_56 = PC1.output(key_64);

	for (int i = 0; i < 16; ++i)
	{
		BinaryNumber temp = key_56.subset(1, 28).rotate_left(Rotations[i]);
		temp.append(key_56.subset(29, 28).rotate_left(Rotations[i]));
		key_56 = temp;
		K[i] = PC2.output(temp);
	}
}

BinaryNumber round(BinaryNumber text, BinaryNumber key_48)
{
	BinaryNumber result = text.subset(33, 32);
	result.append(text.subset(1, 32) ^ des_function.output(text.subset(33, 32), key_48));
	return result;
}

BinaryNumber DES_Encryption(BinaryNumber plaintext)
{
	BinaryNumber text = IP.output(plaintext);
	for (int i = 0; i < 16; ++i)
	{
		text = round(text, K[i]);
	}

	BinaryNumber result = text.subset(33, 32);
	result.append(text.subset(1, 32));
	return IP_Inv.output(result);
}

BinaryNumber DES_Decryption(BinaryNumber ciphertext)
{
	BinaryNumber text = IP.output(ciphertext);
	for (int i = 15; i >= 0; --i)
	{
		text = round(text, K[i]);
	}
	BinaryNumber result = text.subset(33, 32);
	result.append(text.subset(1, 32));
	return IP_Inv.output(result);
}

int main(void)
{
	BinaryNumber key_64, ciphertext;
	cin >> key_64;
	cin >> ciphertext;

	int n;
	cin >> n;

	key_generation(key_64);
	for (int i = 0; i < n; ++i)
	{
		ciphertext = DES_Decryption(ciphertext);
	}
	cout << ciphertext;

	return 0;
}