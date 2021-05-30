#include <iostream>
#include "task.h"
#include<cmath>

int factorial(int x)
{
	if (x <= 0) return 1;
	return x * factorial(x - 1);
}
int main()
{
	setlocale(0, "");
	srand(time(NULL));
	Shop s(5, 10, 100, 7,3);
	while (s.score_req < s.score_buyers)
	{
		s.score_req++;
		this_thread::sleep_for(chrono::milliseconds(10));
		s.mu.lock();
		if (s.length_queue > s.max_len_deque)
		{
			cout << " ������ #" << s.served + s.unserved + 1 << " ��������" << endl;
			s.served++;
		}
		else
		{
			Buyer b = Buyer();
			s.buyers.push_back(b);
			s.length_queue++;
		}
		s.mu.unlock();
	}
	int otn = s.otnoshenie(s.served, s.unserved);
	cout << "����������������/����������: " << otn << endl;
	cout << "������� ����� ������� � �������: " << s.average_time_ojidaniya / s.unserved << endl;
	cout << "�������� ��������� ������ �� �����: " << s.average_time_serv / s.unserved << endl;
	cout << "������� ����� ������ �����: " << s.work_time << endl;
	cout << "������� ����� ������� �����: " << s.Average_time_wait / s.score_cass << endl;
	s.work_time = s.work_time / s.score_cass;
	double l = s.score_buyers * 1000.0 / s.work_time;
	double nu = 1000.0 / s.average_time_serv;
	double P0 = 1.;
	for (int i = 1; i <= s.score_cass; i++)
	{
		P0 += pow(l / nu, i) / factorial(i);
	}
	for (int i = s.score_cass + 1; i < s.score_cass + s.max_len_deque; i++)
	{
		P0 += pow(l / nu, i) / (factorial(s.score_cass) * pow(s.score_cass, i - s.score_cass));
	}
	P0 = double(pow(P0,-1));
	double Veroyatnost_reject = pow(l / nu, s.score_cass + s.max_len_deque) * P0 / (pow(s.score_cass, s.max_len_deque) * factorial(s.score_cass));
	double Otnositelnaya = 1. - Veroyatnost_reject;
	double Absolute = l * Otnositelnaya;
	cout << "���������� ���������� �����������: " << Absolute << "\t����������� ������: " << Veroyatnost_reject << "\t������������� ���������� ����������� ��������: " << Otnositelnaya << endl;

	/*for (int i = 0; i < s.score_cass; ++i)
	{
		s.threads[i].join();
	}*/
	return 0;
}