#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <stack>

using namespace std;

class BinaryNumber {
public:
	BinaryNumber() : binary_number("") {}

	BinaryNumber(const string &s)
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
			c += binary_number[i-1];
			out.append(c);
		}
		return out;
	}

	size_t size() const
	{
		return binary_number.size();
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
	PermutationBox(unsigned short S) : permutation_box(S) {}
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

class SBox {
public:
	SBox(vector<vector<unsigned short>> &&il): s_box(il) {}

	BinaryNumber output(const BinaryNumber& in)
	{
		BinaryNumber row = in.subset(1,1);
		row.append(in.subset(6, 1));
		
		BinaryNumber col = in.subset(2, 4);

		return s_box[row][col];
	}

private:
	vector<vector<unsigned short>> s_box;
};

int main(void)
{
	SBox s1({
		{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
		{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
		{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
		{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
	});
	SBox s2({
		{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
		{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
		{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
		{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
	});
	SBox s3({
		{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
		{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
		{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
		{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
	});	
	SBox s4({												 
		{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
		{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
		{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
		{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
	});	
	SBox s5({
		{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
		{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
		{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
		{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
	});
	SBox s6({
		{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
		{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
		{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
		{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
	});
	SBox s7({
		{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
		{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
		{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
		{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
	});
	SBox s8({
		{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
		{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
		{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
		{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11},
	});

	BinaryNumber input;
	BinaryNumber output;

	cin >> input;
	output.append(s1.output(input.subset(1, 6)));
	output.append(s2.output(input.subset(7, 6)));
	output.append(s3.output(input.subset(13, 6)));
	output.append(s4.output(input.subset(19, 6)));
	output.append(s5.output(input.subset(25, 6)));
	output.append(s6.output(input.subset(31, 6)));
	output.append(s7.output(input.subset(37, 6)));
	output.append(s8.output(input.subset(43, 6)));
	
	cout << output;
	return 0;
}