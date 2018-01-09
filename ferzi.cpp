#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <climits>
#include <utility>
#include <cmath>
#include <cassert>
#include <string>

using namespace std;

using std::vector;

const int N = 40;

//Простая печать позиций
void print(vector<int> const & v) 
{
	char ch = 'a';
	for (int i = 0; i < N; i++) {
		if (N <= 26) 
		{
			cout << ch << v[i] << ' ';
			ch++;
		}
		else
			std::cout << v[i] << ' ';
	}
	cout << endl;
}

//Печать доски (до 39)
void print_table(vector<int> const & v)
{
	for (int i = 0; i < N; i++) {
		cout << "|";
		for (int j = 0; j < v[i] - 1; j++)
			cout << "_|";
		cout << "X|";
		for (int k = v[i]; k < N; k++)
			cout << "_|";
		cout << endl;
	}
}

//Счетчик неправильных расстановок - целевая функция
int count_attacks(vector<int> const & verticals) 
{
	int res = 0;
	for (int i = 0; i < N - 1; i++)
		for (int j = i + 1; j < N; j++)
		{
			if (verticals[i] == verticals[j] //если столкновения на одной строке
				|| abs(verticals[j] - verticals[i]) == j - i) //на диагонали
				++res;
		}
	//cout << "Attacks:" << res << endl;
	return res;
}

//вероятность, с которой осуществляется переход в другую ячейку
double probability(int delta, double Tempr)
{
	return exp(-delta / Tempr);
}


vector<int> arrangement()
{
	const double alpha = 0.5; //коэффициент для понижения температуры
	const double start_Tempr = 100; //стартовая температура
	const int It_interval = 5;	

	vector<int> new_vector(N); //Старое решение
	for (int i = 0; i < N; i++) 
		new_vector[i] = i + 1;

	vector<int> old_vector = new_vector; //Новое решение
	
	int old_cnt_attacks = INT_MAX; //Новое количество атак
	int it = 0;
	double Tempr = start_Tempr;

	while (old_cnt_attacks && Tempr > 0)
	{
		//print_table(ol_vector);
		//cout << endl;
		swap(old_vector[rand() % N], old_vector[rand() % N]); //Получаем новое случайное решение меняя позиции в новом решении

		int new_count_attacks = count_attacks(old_vector); 

		if (new_count_attacks <= old_cnt_attacks //если новое решение не хуже старого
			|| new_count_attacks > old_cnt_attacks && rand() % 100 + 1 <= probability(new_count_attacks - old_cnt_attacks, Tempr) * 100)
		{
			new_vector = old_vector;
			old_cnt_attacks = new_count_attacks;
		}
		else
			old_vector = new_vector;

		if (it == It_interval) //Понижение температуры
		{
			Tempr *= alpha;
			it = 0;
		}
		++it;
	}
	return old_vector;
}



int main()
{
	srand(time(nullptr));

	cout << endl;
	time_t start = clock();
	//print_table(arrangement());
	print(arrangement());
	cout << "Time of arrangment: " << double(clock() - start) / CLOCKS_PER_SEC << " seconds\n";
	system("pause");
}
