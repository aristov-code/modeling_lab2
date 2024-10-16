#include <iostream>
#include <vector>
#include <fstream>


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
			sequence.push_back(double(prev) / UINT32_MAX);
			next = mid_square(prev);
			sequence.push_back(double(next) / UINT32_MAX);
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

void count_on_intervals(vector<double> s, int m = 50)
{
	float interval = 5. / m; // Длина одного интервала
	int count;
	fstream fout;
	fout.open("count_of_numbers.txt"); // Будем записывать количество чисел на каждом интервале в файл
	for (int i = 1; i < m + 1; i++)
	{
		count = 0;
		for (int j = 0; j < s.size(); j++)
		{
			if (s[j] * UINT32_MAX >= ((i - 1) * interval + 1) * UINT32_MAX && s[j] * UINT32_MAX < (i * interval + 1) * UINT32_MAX)
			{
				count++;
			}
		}
		cout << "Количество чисел на полуинтервале [" << (i - 1) * interval + 1<< ", " << i * interval + 1<< "): " << count << endl;
		fout << count << "\n";
	}
	fout.close();
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
	count_on_intervals(s);
	return 0;
}