#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <stack>
#include <array>
#include <vector>

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
		for (int i = 8 - bit_num; len > 0; ++i, --len)
		{
			string c;
			c += binary_number[i - 1];
			out.append(c);
		}
		return out;
	}
	
	BinaryNumber subset(size_t bit_num) const
	{
		BinaryNumber out;
		for (int i = 7; i >= 0; --i)
		{
			if (i != bit_num)
			{
				out.append(BinaryNumber("0"));
			}
			else
			{
				out.append(BinaryNumber("1"));
			}
		}
		return out;
	}

	size_t size() const
	{
		return binary_number.size();
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

istream& operator>>(istream& is, BinaryNumber& binary_number) {
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

ostream& operator<<(ostream& os, const BinaryNumber& binary_number) {
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

BinaryNumber operator^(const BinaryNumber& lhs, const BinaryNumber& rhs)
{
	BinaryNumber result;
	for (size_t i = 0; i < rhs.size(); ++i)
	{
		if (lhs[i] == rhs[i])
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

int main() 
{
	BinaryNumber a, b, addition;
	vector<BinaryNumber> multiplication;
	BinaryNumber mul("00000000");

	cin >> a >> b;
	
	addition = a ^ b;
	multiplication.push_back(a);

	for (int i = 1; i < 8; ++i)
	{
		if (static_cast<string>(multiplication.back().subset(7, 1)) == "1")
		{
			multiplication.push_back(multiplication.back().operator<<(1) ^ BinaryNumber("00011011"));
		}
		else
		{
			multiplication.push_back(multiplication.back().operator<<(1));
		}
	}

	for (int i = 7; i >= 0; --i)
	{
		BinaryNumber temp = multiplication.back();
		multiplication.pop_back();
		if (static_cast<string>(b.subset(i, 1)) == "1")
		{
			mul = mul ^ temp;
		}
	}

	std::cout << addition;
	std::cout << " ";
	std::cout << mul;

	return 0;
}
