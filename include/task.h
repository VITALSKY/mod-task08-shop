#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;

class Buyer
{
public:
	chrono::system_clock::time_point start;
	Buyer();
	int ojidanie();
};
class Shop
{
public:
	int served = 0;
	int unserved = 0;
	int score_req = 0;
	double average_time_serv = 0;
	double average_time_ojidaniya = 0;
	double Average_time_wait = 0;
	double work_time = 0;
	int length_queue = 0;
	int score_cass;
	int score_buyers;
	int service_time;
	int score_prod;
	int max_len_deque;
	vector<thread> threads;
	vector<Buyer> buyers;
	mutex mu;
public:
	Shop(int score_cass, int score_buyers, int service_time, int score_prod, int max_len_deque);
	void in_proccess();
	double otnoshenie(int served, int unserved);
};
