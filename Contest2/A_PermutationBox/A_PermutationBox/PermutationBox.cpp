#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class BinaryNumber {
public:
	BinaryNumber(): binary_number("") {}
	BinaryNumber(string s) 
	{
		for (size_t i = 0; i < s.length(); ++i)
		{
			switch (s[i])
			{
			case '0':
				binary_number += "0000";
				break;
			case '1':
				binary_number += "0001";
				break;
			case '2':
				binary_number += "0010";
				break;
			case '3':
				binary_number += "0011";
				break;
			case '4':
				binary_number += "0100";
				break;
			case '5':
				binary_number += "0101";
				break;
			case '6':
				binary_number += "0110";
				break;
			case '7':
				binary_number += "0111";
				break;
			case '8':
				binary_number += "1000";
				break;
			case '9':
				binary_number += "1001";
				break;
			case 'A':
				binary_number += "1010";
				break;
			case 'B':
				binary_number += "1011";
				break;
			case 'C':
				binary_number += "1100";
				break;
			case 'D':
				binary_number += "1101";
				break;
			case 'E':
				binary_number += "1110";
				break;
			case 'F':
				binary_number += "1111";
				break;
			default:
				throw invalid_argument("invalid HexNumber char");
			}
		}
	}

	operator string() const 
	{
		string s;
		for (size_t i = 0; i < binary_number.size(); i += 4)
		{
			if (binary_number[i] == '0' && binary_number[i+1] == '0' &&
				binary_number[i + 2] == '0' && binary_number[i + 3] == '0')
			{
				s += '0';
			}
			else if (binary_number[i] == '0' && binary_number[i + 1] == '0' &&
					 binary_number[i + 2] == '0' && binary_number[i + 3] == '1')
			{
				s += '1';
			}
			else if (binary_number[i] == '0' && binary_number[i + 1] == '0' &&
				binary_number[i + 2] == '1' && binary_number[i + 3] == '0')
			{
				s += '2';
			}
			else if (binary_number[i] == '0' && binary_number[i + 1] == '0' &&
				binary_number[i + 2] == '1' && binary_number[i + 3] == '1')
			{
				s += '3';
			}
			else if (binary_number[i] == '0' && binary_number[i + 1] == '1' &&
				binary_number[i + 2] == '0' && binary_number[i + 3] == '0')
			{
				s += '4';
			}
			else if (binary_number[i] == '0' && binary_number[i + 1] == '1' &&
				binary_number[i + 2] == '0' && binary_number[i + 3] == '1')
			{
				s += '5';
			}
			else if (binary_number[i] == '0' && binary_number[i + 1] == '1' &&
				binary_number[i + 2] == '1' && binary_number[i + 3] == '0')
			{
				s += '6';
			}
			else if (binary_number[i] == '0' && binary_number[i + 1] == '1' &&
				binary_number[i + 2] == '1' && binary_number[i + 3] == '1')
			{
				s += '7';
			}
			else if (binary_number[i] == '1' && binary_number[i + 1] == '0' &&
				binary_number[i + 2] == '0' && binary_number[i + 3] == '0')
			{
				s += '8';
			}
			else if (binary_number[i] == '1' && binary_number[i + 1] == '0' &&
				binary_number[i + 2] == '0' && binary_number[i + 3] == '1')
			{
				s += '9';
			}
			else if (binary_number[i] == '1' && binary_number[i + 1] == '0' &&
				binary_number[i + 2] == '1' && binary_number[i + 3] == '0')
			{
				s += 'A';
			}
			else if (binary_number[i] == '1' && binary_number[i + 1] == '0' &&
				binary_number[i + 2] == '1' && binary_number[i + 3] == '1')
			{
				s += 'B';
			}
			else if (binary_number[i] == '1' && binary_number[i + 1] == '1' &&
				binary_number[i + 2] == '0' && binary_number[i + 3] == '0')
			{
				s += 'C';
			}
			else if (binary_number[i] == '1' && binary_number[i + 1] == '1' &&
				binary_number[i + 2] == '0' && binary_number[i + 3] == '1')
			{
				s += 'D';
			}
			else if (binary_number[i] == '1' && binary_number[i + 1] == '1' &&
				binary_number[i + 2] == '1' && binary_number[i + 3] == '0')
			{
				s += 'E';
			}
			else if (binary_number[i] == '1' && binary_number[i + 1] == '1' &&
				binary_number[i + 2] == '1' && binary_number[i + 3] == '1')
			{
				s += 'F';
			}
		}

		return s;
	}

	char& operator[](size_t i)
	{
		return binary_number[i];
	}
	
	const char& operator[](size_t i) const
	{
		return binary_number[i];
	}

	BinaryNumber& operator+=(const char c)
	{
		binary_number += c;
		return *this;
	}

private:
	string binary_number;
};

istream& operator>>(istream& is, BinaryNumber& binary_number)
{
	string s;
	is >> s;
	binary_number = s;
	return is;
}

ostream& operator<<(ostream& os, const BinaryNumber& binary_number)
{
	string s = binary_number;
	os << s;
	return os;
}

class PermutationBox {
public:
	PermutationBox(unsigned short S): permutation_box(S) {}
	unsigned short& operator[](size_t i)
	{
		return permutation_box[i];
	}

	BinaryNumber output(const BinaryNumber& input)
	{
		BinaryNumber out;
		for (int i = 0; i < permutation_box.size(); ++i)
		{
			out += input[permutation_box[i]-1];
		}
		return out;
	}

private:
	vector<unsigned short> permutation_box;
};

int main(void)
{
	unsigned short S, N;
	cin >> S;
	
	PermutationBox permutation_box(S);
	for (int i = 0; i < S; ++i)
	{
		cin >> permutation_box[i];
	}

	cin >> N;
	
	BinaryNumber input;
	cin >> input;

	cout << permutation_box.output(input);


	return 0;
}