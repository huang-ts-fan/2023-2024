#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <deque>
#include <unordered_set>
#include <unordered_map>

#include <chrono>

#include "Node.h"

using namespace std;

int main()
{
	std::cerr << "\nHello World!";

	/*int minimum_size_of_set(10);
	std::set<int> myset;
	myset.insert(1);
	myset.insert(1);
	myset.insert(1);
	myset.insert(1);
	myset.insert(3);
	cerr << "\nmy size: " << myset.size();
	while (myset.size() < 10)
	{
		myset.insert(rand());
		cerr << "\nmy size (new): " << myset.size();
	}
	cerr << "\nFinished";
	system("pause");*/

	//creating our containers
	vector<double> v1;
	set<double> s1;
	unordered_set<double> us1;
	map<double, double> m1;
	multimap<double, double> mm1;

	const int max_size(1e7);
	//adding 100 random items to the containers
	auto clock1(chrono::steady_clock::now());
	for (int i = 0; i < max_size; ++i)
	{
		const double j(rand()%100000/100000.);
		v1.push_back(j);
	}
	auto clock1f(chrono::steady_clock::now());

	auto clock2(chrono::steady_clock::now());
	for (int i = 0; i < max_size; ++i)
	{
		const double j(rand() % 100000 / 100000.);
		s1.insert(j);
	}
	auto clock2f(chrono::steady_clock::now());
	
	auto clock3(chrono::steady_clock::now());
	for (int i = 0; i < max_size; ++i)
	{
		const double j(rand() % 100000 / 100000.);
		us1.insert(j);
	}
	auto clock3f(chrono::steady_clock::now());

	auto clock4(chrono::steady_clock::now());
	for (int i = 0; i < max_size; ++i)
	{
		const double j(rand() % 100000 / 100000.);
		m1.insert(make_pair(j, static_cast<double>(i)));
	}
	auto clock4f(chrono::steady_clock::now());

	auto clock5(chrono::steady_clock::now());
	for (int i = 0; i < max_size; ++i)
	{
		const double j(rand() % 100000 / 100000.);
		mm1.insert(make_pair(j, static_cast<double>(i)));
	}
	auto clock5f(chrono::steady_clock::now());

	/*cerr << "\n*******Vector Data:";
	for (auto& item : v1)
		cerr << "\t" << ++item;
	cerr << "\n*******Set Data:";
	for (auto item : s1)
		cerr << "\t" << item;
	cerr << "\n*******Unordered Set Data:";
	for (auto item : us1)
		cerr << "\t" << item;
	cerr << "\n*******Map Data:";
	for (auto item_pair : m1)
		cerr << "\t(" << item_pair.first << ","  << item_pair.second << ")";
	cerr << "\n*******Multimap Data:";
	for (auto item_pair : mm1)
		cerr << "\t(" << item_pair.first << "," << item_pair.second << ")";*/

	cerr << "\n*******Vector Size:" << v1.size() << " time: " << chrono::duration_cast<chrono::milliseconds>(clock1f-clock1).count();
	cerr << "\n*******Set Size:" << s1.size() << " time: " << chrono::duration_cast<chrono::milliseconds>(clock2f - clock2).count();
	cerr << "\n*******Unordered Set Size:" << us1.size() << " time: " << chrono::duration_cast<chrono::milliseconds>(clock3f - clock3).count();
	cerr << "\n*******Map Size:" << m1.size() << " time: " << chrono::duration_cast<chrono::milliseconds>(clock4f - clock4).count();
	cerr << "\n*******Multimap Size:" << mm1.size() << " time: " << chrono::duration_cast<chrono::milliseconds>(clock5f - clock5).count();

	system("pause");
}