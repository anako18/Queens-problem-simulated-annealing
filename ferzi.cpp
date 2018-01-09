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

//������� ������ �������
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

//������ ����� (�� 39)
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

//������� ������������ ����������� - ������� �������
int count_attacks(vector<int> const & verticals) 
{
	int res = 0;
	for (int i = 0; i < N - 1; i++)
		for (int j = i + 1; j < N; j++)
		{
			if (verticals[i] == verticals[j] //���� ������������ �� ����� ������
				|| abs(verticals[j] - verticals[i]) == j - i) //�� ���������
				++res;
		}
	//cout << "Attacks:" << res << endl;
	return res;
}

//�����������, � ������� �������������� ������� � ������ ������
double probability(int delta, double Tempr)
{
	return exp(-delta / Tempr);
}


vector<int> arrangement()
{
	const double alpha = 0.5; //����������� ��� ��������� �����������
	const double start_Tempr = 100; //��������� �����������
	const int It_interval = 5;	

	vector<int> new_vector(N); //������ �������
	for (int i = 0; i < N; i++) 
		new_vector[i] = i + 1;

	vector<int> old_vector = new_vector; //����� �������
	
	int old_cnt_attacks = INT_MAX; //����� ���������� ����
	int it = 0;
	double Tempr = start_Tempr;

	while (old_cnt_attacks && Tempr > 0)
	{
		//print_table(ol_vector);
		//cout << endl;
		swap(old_vector[rand() % N], old_vector[rand() % N]); //�������� ����� ��������� ������� ����� ������� � ����� �������

		int new_count_attacks = count_attacks(old_vector); 

		if (new_count_attacks <= old_cnt_attacks //���� ����� ������� �� ���� �������
			|| new_count_attacks > old_cnt_attacks && rand() % 100 + 1 <= probability(new_count_attacks - old_cnt_attacks, Tempr) * 100)
		{
			new_vector = old_vector;
			old_cnt_attacks = new_count_attacks;
		}
		else
			old_vector = new_vector;

		if (it == It_interval) //��������� �����������
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
