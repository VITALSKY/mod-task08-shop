#include "task.h"

using namespace std;

Buyer::Buyer()
{
	start = chrono::system_clock::now();
}

int Buyer::ojidanie()
{
	chrono::system_clock::time_point now = chrono::system_clock::now();
	int res = chrono::duration_cast<chrono::milliseconds>(now - start).count();
	return res;
}



Shop::Shop(int score_cass, int score_buyers, int service_time, int score_prod, int max_len_deque)
{
	this->max_len_deque = max_len_deque;
	this->score_prod = score_prod;
	this->score_cass = score_cass;
	this->score_buyers = score_buyers;
	this->service_time = service_time;
	for (int i = 0; i < score_cass; i++)
	{
		threads.push_back(thread(&Shop::in_proccess, this));
		threads[i].detach();
	}
}
double Shop::otnoshenie(int served, int unserved)
{
	return served / unserved;
}

void Shop::in_proccess()
{
	srand(time(0));
	while (served + unserved < score_buyers)
	{
		mu.lock();
		if (length_queue > 0)
		{
			length_queue--;
			average_time_ojidaniya += buyers.front().ojidanie();
			mu.unlock();
		}
		else
		{
			Average_time_wait += 5;
			this_thread::sleep_for(std::chrono::milliseconds(5));
			mu.unlock();
			continue;
		}
		int count_buy = rand() % (score_prod / 2) + score_prod;
		for (int i = 0; i < count_buy; ++i)
		{
			this_thread::sleep_for(chrono::milliseconds(service_time));
		}
		mu.lock();
		work_time += (double)count_buy * service_time;
		average_time_serv += (double)count_buy * service_time;
		cout << "клиент # " << served + unserved + 1 << " обслужен \n";
		unserved++;
		mu.unlock();
	}
}

