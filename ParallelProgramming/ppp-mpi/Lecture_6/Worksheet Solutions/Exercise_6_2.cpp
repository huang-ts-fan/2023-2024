#include <mpi.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <time.h>
#include <string>
#include <chrono>

using namespace std;

#define DO_TIMING

const int imax = 401, jmax = 101;
const double L = 2.0, W = 0.5;


class Cmatrix
{
public:
	double* mat_1D;
	double** mat_2D;
	int n, m;

	Cmatrix()
	{
		mat_1D = nullptr;
		mat_2D = nullptr;
	}
	Cmatrix(int imax, int jmax)
	{
		n = imax;
		m = jmax;
		mat_1D = new double[n * m];
		mat_2D = new double* [n];
		for (int i = 0; i < n; i++)
			mat_2D[i] = &mat_1D[i * m];
	}
	~Cmatrix()
	{
		delete[] mat_1D;
		delete[] mat_2D;
	}

	void to_tab_file(string fname)
	{
		fstream fout;
		fout.open(fname, ios::out);
		if (fout.fail())
		{
			cout << "Error openin file!" << endl;
			cout.flush();
			exit(0);
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				fout << mat_2D[i][j] << "\t";
			fout << endl;
		}
		fout.close();
	}
};

class CWorld
{
public:
	Cmatrix* Psi, * Psi_old;
	double dx;

	int id, p;
	int tag_num;

	vector<int> num_i, start_i;

	void set_BC();
	void setup();
	void do_iterations(double tol);
	void run_world();
};

void CWorld::set_BC()
{
	//Initial values for internal points
	for (int i = 0; i < num_i[id] + 2; i++)
		for (int j = 0; j < jmax; j++)
			Psi->mat_2D[i][j] = 0.0;

	//Top and bottom boundaries
	for (int i = 0; i < num_i[id]; i++)
	{
		double x = dx * (i + start_i[id]);

		Psi->mat_2D[i + 1][0] = 1.25 * (2 * x - 0.5 * x * x) - 2.5;
		Psi->mat_2D[i + 1][jmax - 1] = 2.5 - 1.25 * (2 * x - 0.5 * x * x);
	}

	//Left and right boundaries
	for (int j = 0; j < jmax; j++)
	{
		double y = dx * j;
		if (id == 0)
			Psi->mat_2D[1][j] = 10 * y - 2.5;
		if (id == p-1)
			Psi->mat_2D[num_i[id]][j] = 0;
	}

	//Copy initial and boundary values into Psi_old
	for (int i = 0; i < num_i[id] + 2; i++)
		for (int j = 0; j < jmax; j++)
			Psi_old->mat_2D[i][j] = Psi->mat_2D[i][j];
}

void CWorld::setup()
{
	tag_num = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	int i_rem = imax;
	int i_s = 0;
	num_i.resize(p);
	start_i.resize(p);

	for (int n = 0; n < p; n++)
	{
		start_i[n] = i_s;
		num_i[n] = i_rem / (p - n);
		i_rem -= num_i[n];
		i_s += num_i[n];
	}

	Psi = new Cmatrix(num_i[id] + 2, jmax);
	Psi_old = new Cmatrix(num_i[id] + 2, jmax);

	dx = L / (imax - 1);

	set_BC();
}

void CWorld::do_iterations(double tol)
{
	double a = 1.0, b = 1.0, c = 1.0, d = 1.0, e = -4.0, f = 0.0;
	double resid_vals[2];
	int cnt = 0;
	MPI_Request requests[4];
	int req_cnt;

	resid_vals[0] = tol * 10;

	while (resid_vals[0] > tol)
	{
		req_cnt = 0;
		//LHS
		if (id != 0)
		{
			MPI_Irecv(&Psi_old->mat_2D[0][0], jmax, MPI_DOUBLE, id - 1, tag_num, MPI_COMM_WORLD, &requests[req_cnt]);
			req_cnt++;
			MPI_Isend(&Psi_old->mat_2D[1][0], jmax, MPI_DOUBLE, id - 1, tag_num, MPI_COMM_WORLD, &requests[req_cnt]);
			req_cnt++;
		}
		//RHS
		if (id != p - 1)
		{
			MPI_Irecv(&Psi_old->mat_2D[num_i[id]+1][0], jmax, MPI_DOUBLE, id + 1, tag_num, MPI_COMM_WORLD, &requests[req_cnt]);
			req_cnt++;
			MPI_Isend(&Psi_old->mat_2D[num_i[id]][0], jmax, MPI_DOUBLE, id + 1, tag_num, MPI_COMM_WORLD, &requests[req_cnt]);
			req_cnt++;
		}

		resid_vals[0] = 0.0;
		resid_vals[1] = 0.0;
		//loop over internal points to do calculation
		for (int i = 2; i < num_i[id]; i++)
			for (int j = 1; j < jmax - 1; j++)
			{
				Psi->mat_2D[i][j] = (1.0 / e) * (f - (a * Psi_old->mat_2D[i + 1][j] + b * Psi_old->mat_2D[i - 1][j] + c * Psi_old->mat_2D[i][j + 1] + d * Psi_old->mat_2D[i][j - 1]));
				resid_vals[0] += fabs(Psi->mat_2D[i][j] - Psi_old->mat_2D[i][j]);
				resid_vals[1] += fabs(Psi->mat_2D[i][j]);
			}

		MPI_Waitall(req_cnt, requests, MPI_STATUSES_IGNORE);

		for (int j = 1; j < jmax - 1; j++)
		{
			if (id != 0)
			{
				int i = 1;
				Psi->mat_2D[i][j] = (1.0 / e) * (f - (a * Psi_old->mat_2D[i + 1][j] + b * Psi_old->mat_2D[i - 1][j] + c * Psi_old->mat_2D[i][j + 1] + d * Psi_old->mat_2D[i][j - 1]));
				resid_vals[0] += fabs(Psi->mat_2D[i][j] - Psi_old->mat_2D[i][j]);
				resid_vals[1] += fabs(Psi->mat_2D[i][j]);
			}
			if (id != p - 1)
			{
				int i = num_i[id];
				Psi->mat_2D[i][j] = (1.0 / e) * (f - (a * Psi_old->mat_2D[i + 1][j] + b * Psi_old->mat_2D[i - 1][j] + c * Psi_old->mat_2D[i][j + 1] + d * Psi_old->mat_2D[i][j - 1]));
				resid_vals[0] += fabs(Psi->mat_2D[i][j] - Psi_old->mat_2D[i][j]);
				resid_vals[1] += fabs(Psi->mat_2D[i][j]);
			}
		}

		//swap matrix pointers - now need to copy data, which is slow
		Cmatrix* temp = Psi;
		Psi = Psi_old;
		Psi_old = temp;

		//Combine values to calculate the residual
		MPI_Allreduce(MPI_IN_PLACE, resid_vals, 2, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
		resid_vals[0] = resid_vals[0] / max(resid_vals[1], 1.0e-10);

#ifndef DO_TIMING
		if (cnt % 100 == 0 && id == 0)
			cout << cnt << ":\t" << resid_vals[0] << endl;
#endif

		cnt++;
		tag_num++;
	}
}

void CWorld::run_world()
{
	setup();

#ifdef DO_TIMING
	MPI_Barrier(MPI_COMM_WORLD);
	auto start = chrono::high_resolution_clock::now();
#endif

	do_iterations(1.e-6);

	MPI_Barrier(MPI_COMM_WORLD);
#ifdef DO_TIMING
	auto finish = chrono::high_resolution_clock::now();
	if (id == 0)
	{
		std::chrono::duration<double> elapsed = finish - start;
		cout << setprecision(5);
		cout << "The code took " << elapsed.count() << "s to run" << endl;
	}
#endif

	string fname;

	fname = "output_" + to_string(id) + ".txt";

	Psi->to_tab_file(fname);

	delete Psi;
	delete Psi_old;
}

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	CWorld World;

	World.run_world();

	MPI_Finalize();
	return 0;
}
