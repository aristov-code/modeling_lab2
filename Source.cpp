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
vector<double> generate_mid_square()
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

// Функция распределения
double F(double x)
{
	if (x >= 1 && x <= 2)
		return 1. / 7. * (x - 1) * (x - 1);

	if (x >= 2 && x <= 4)
		return 2. / 7. * x - 3. / 7.;

	if (x >= 4 && x <= 6)
		return 1. / 7. * x + 1. / 7.;
}

// Обратная функция
double X(double f)
{
	if (f >= 0 && f <= 1. / 7.)
		return 1 + sqrt(7 * f);

	if (f >= 1. / 7. && f <= 5. / 7.)
		return 3.5 * f + 1.5;

	if (f >= 5. / 7. && f <= 1)
		return 7 * f - 1;
}

// Генератор случайных чисел с заданным законом распределения
vector<double> generate()
{
	vector<double> sequence = generate_mid_square();
	vector<double> generated_sequence;
	double u = 0;
	for (int i = 0; i < sequence.size(); i++)
	{
		u = X(sequence[i]);
		generated_sequence.push_back(u);
	}
	return generated_sequence;
}

//Подсчет количества чисел на интервалах
vector<int> quantity_on_intervals(vector<double> s, const int A, const int B, int m = 50)
{
	vector<int> quantity(m);
	int n = 0;
	for (int i = 0; i < s.size(); i++)
	{
		n = int(ceil(((s[i] - A)  / (B - A)) * m) - 1);
		quantity[n] += 1;
	}

	return quantity;
}

// Расчет ожидаемого количества чисел на интервалах
vector<double> find_expected_quantity(int sequence_size, const int A, const int B, int m = 50)
{
	vector<double> quantity(m);
	double length = double((B - A)) / double(m);
	double left_val = 0, right_val = 0;
	for (int i = 0; i < m; i++)
	{
		left_val = F(i * length + 1);
		right_val = F((i + 1) * length + 1);

		quantity[i] = (right_val - left_val) * sequence_size;
	}

	return quantity;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout.precision(11);

	ofstream fout;
	fout.open("count_of_numbers.txt");

	vector<double> s = generate();
	vector<int> c = quantity_on_intervals(s, 1, 6);
	vector<double> exp = find_expected_quantity(s.size(), 1, 6);

	for (int i = 0; i < c.size(); i++)
		fout << c[i] << endl;

	fout.close();

	fout.open("expected_numbers.txt");

	for (int i = 0; i < exp.size(); i++)
		fout << exp[i] << endl;

	fout.close();
	
	return 0;
}