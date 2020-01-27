#include <iostream>
#include <vector>
#include <stdexcept>
#include <set>

using namespace std;

class PermutationBox {
public:
	PermutationBox(unsigned short S) : permutation_box(S) {}
	
	unsigned short& operator[](size_t i)
	{
		return permutation_box[i];
	}

	bool inverse(PermutationBox &inv)
	{
		set<unsigned short> numbers_in_PermutationBox;
		vector<bool> seen(inv.permutation_box.size(), false);

		for (int i = 0; i < permutation_box.size(); ++i)
		{
			if (numbers_in_PermutationBox.insert(permutation_box[i]).second == true)
			{
				inv[permutation_box[i] - 1] = i + 1;
				seen[permutation_box[i] - 1] = true;
			}
		}

		for (auto i : seen)
		{
			if (i == false)
			{
				return false;
			}
		}
		return true;
	}

private:
	vector<unsigned short> permutation_box;
};

int main(void)
{
	unsigned short in, out;
	cin >> in;
	cin >> out;

	PermutationBox permutation_box(out);
	for (int i = 0; i < out; ++i)
	{
		cin >> permutation_box[i];
	}

	PermutationBox inverse_permutation_box(in);

	if (permutation_box.inverse(inverse_permutation_box))
	{
		for (int i = 0; i < in; ++i)
		{
			cout << inverse_permutation_box[i] << " ";
		}
	}
	else
	{
		cout << "IMPOSSIBLE";
	}

	return 0;
}