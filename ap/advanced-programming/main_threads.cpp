#include <iostream>				
#include <thread>
#include <chrono>

/*using namespace std;

static const int num_threads = 10;

void call_from_thread()
{
	std::cout << "Hello, World" << std::endl;
}

void call_from_thread_with_param(int i)
{
	std::cout << "Thread " << i << std::endl;
}

int maint()
{
	std::thread t[num_threads];

	//Launch a group of threads
	for (int i = 0; i < num_threads; ++i)
	{
		//t[i] = std::thread(call_from_thread);
		t[i] = std::thread(call_from_thread_with_param, i);
	}

	std::cout << "Launched from the main\n";

	//Join the threads with the main thread
	for (int i = 0; i < num_threads; ++i)
	{
		t[i].join();
	}

	system("pause");
	return 0;
}
*/

/*
//A Complete C++ Program For Multithreading

//A C++ program is given below. It launches three threads from the main function. Each thread is called using one of the callable objects specified above.

// C++ program to demonstrate
// multithreading using three
// different callables.
#include <iostream>
#include <thread>
using namespace std;

// A dummy function
void foo(int Z)
{
	for (int i = 0; i < Z; i++) {
		cout << "Thread using function"
				" pointer as callable\n";
	}
}

// A callable object
class thread_obj {
public:
	void operator()(int x)
	{
		for (int i = 0; i < x; i++)
			cout << "Thread using function"
					" object as callable\n";
	}
};

// class definition
class Base {
public:
	// non-static member function
	void foo()
	{
		cout << "Thread using non-static member function "
				"as callable"
			<< endl;
	}
	// static member function
	static void foo1()
	{
		cout << "Thread using static member function as "
				"callable"
			<< endl;
	}
};

// Driver code
int main()
{
	cout << "Threads 1 and 2 and 3 "
			"operating independently"
		<< endl;

	// This thread is launched by using
	// function pointer as callable
	thread th1(foo, 3);

	// This thread is launched by using
	// function object as callable
	thread th2(thread_obj(), 3);

	// Define a Lambda Expression
	auto f = [](int x) {
		for (int i = 0; i < x; i++)
			cout << "Thread using lambda"
					" expression as callable\n";
	};

	// This thread is launched by using
	// lambda expression as callable
	thread th3(f, 3);

	// object of Base Class
	Base b;

	thread th4(&Base::foo, &b);

	thread th5(&Base::foo1);

	// Wait for the threads to finish
	// Wait for thread t1 to finish
	th1.join();

	// Wait for thread t2 to finish
	th2.join();

	// Wait for thread t3 to finish
	th3.join();

	// Wait for thread t4 to finish
	th4.join();

	// Wait for thread t5 to finish
	th5.join();

	return 0;
}
*/

bool isPrime(long number);
int compute_primes(int amount, long min_value);

int call_from_thread(int inumber)
{
	int id = std::hash < std::thread::id > {}(std::this_thread::get_id());
	srand(id);
	int total = compute_primes(10000 + rand(), 1000000 + rand() % 10);
	//std::cerr << "\nid:" << std::this_thread::get_id();
	std::cerr << ".red." << total;
	return total;
}

int main()
{
	std::cout << "\nMAIN: " << std::this_thread::get_id();
	//serial***********************************************************
	{
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		int j = 0;
		for (int i = 0; i < 100; i++)
		{
			j+=call_from_thread(i);
		}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout << "\nSeconds:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()/1000.;
		std::cout << "\nj: " << j;
	}
	
	//parallel****************************************************************
	{std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	//std::thread t1(call_from_thread);
	//t1.join();//Join the thread with the main thread

	std::thread t[100]; //static array of threads
	//Launch a group of threads
	for (int i = 0; i < 100; ++i) { //creation
		t[i] = std::thread(call_from_thread, rand()%10);
	}
	for (int i = 0; i < 100; ++i) { //deployment
		t[i].join();
	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "\nSeconds (Parallel):" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()/1000.;
	}
	std::cout << "\nDone!\n";
	system("pause");
}