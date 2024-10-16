#include <iostream>
#include <vector>


using namespace std;


// Функция метода середин квадратов
uint64_t mid_square(uint64_t xi)
{
	xi = ((xi * xi) >> 16) & 0xFFFFFFFF;
	return xi;
}

// Функция для генерации последовательности
vector<double> generate_n_numbers()
{
	vector<double> sequence;
	uint64_t prev, next;
	uint64_t seed = 1726506092498;

	while (sequence.size() <= 20000)
	{
		sequence.clear();
		cout << "seed " << seed << endl;
		prev = mid_square(seed);
		sequence.push_back(double(prev) / UINT32_MAX);
		next = mid_square(prev);
		sequence.push_back(double(next) / UINT32_MAX);

		// Пока последовательность не зациклилась или не стала слишком большой
		while (next != prev && sequence.size() < 100000)
		{
			prev = mid_square(next);
			if (prev != 0) sequence.push_back(double(prev) / UINT32_MAX);
			next = mid_square(prev);
			if (next != 0) sequence.push_back(double(next) / UINT32_MAX);
		}

		seed = time(NULL);
	}
	return sequence;
}

vector<double> generate()
{
	vector<double> sequence = generate_n_numbers();
	vector<double> generated_sequence;
	double u = 0;
	for (int i = 0; i < sequence.size(); i++)
	{
		if (sequence[i] >= 0 && sequence[i] <= 1. / 7.)
		{
			u = 1 + sqrt(7 * sequence[i]);
			generated_sequence.push_back(u);
		}
		if (sequence[i] >= 1. / 7. && sequence[i] <= 5. / 7.)
		{
			u = 3.5 * sequence[i] + 1.5;
			generated_sequence.push_back(u);
		}
		if (sequence[i] >= 5. / 7. && sequence[i] <= 1)
		{
			u = 7 * sequence[i] - 1;
			generated_sequence.push_back(u);
		}
	}
	return generated_sequence;
}

vector<double> count_on_intervals(vector<double> s, const int A, const int B, int m = 50)
{
	vector<double> counts(m);
	int n = 0;
	for (int i = 0; i < s.size(); i++)
	{
		n = int(ceil(((s[i] - A)  / (B - A)) * m) - 1);
		counts[n] += 1;
	}

	return counts;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout.precision(11);

	vector<double> s = generate();
	/*
	for (int i = 0; i < s.size(); i++)
	{
		cout << s[i] << endl;
	}*/
	vector<double> c = count_on_intervals(s, 1, 6);
	for (int i = 0; i < c.size(); i++)
	{
		cout << c[i] << endl;
	}
	
	return 0;
}