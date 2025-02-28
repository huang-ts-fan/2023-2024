#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int id, p;

double calc_ave(double *list, int num)
{
	double total = 0.0;
	for (int i = 0; i < num; i++)
		total += list[i];
	return total / num;
}

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	srand(time(NULL) + id * 10);

	int tag_num = 1;
	double *send_data1 = nullptr, send_data2;
	double *recv_data1 = nullptr, recv_data2;
	int num_sendrecv = 20;

	if (id == 0)
	{
		send_data1 = new double[num_sendrecv*p];
		for (int i = 0; i < num_sendrecv*p; i++)
			send_data1[i] = ((double)rand() / (double)RAND_MAX)*100.0;
	}

	recv_data1 = new double[num_sendrecv];

	MPI_Scatter(send_data1, num_sendrecv, MPI_DOUBLE, recv_data1, num_sendrecv, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	send_data2 = calc_ave(recv_data1, num_sendrecv);

	delete[] recv_data1;	//Can be called on all processes as it is NULL where not used
	delete[] send_data1;

	MPI_Reduce(&send_data2, &recv_data2, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (id == 0)
		cout << "The average of all the data is " << recv_data2 / p << endl;

	MPI_Finalize();
}