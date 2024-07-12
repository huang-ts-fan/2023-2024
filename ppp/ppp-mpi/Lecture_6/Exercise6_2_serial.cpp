#include <mpi.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

const int imax = 201, jmax = 51;
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

	void set_BC();
	void setup();
	void do_iterations(double tol);
	void run_world();
};

void CWorld::set_BC()
{
	//Top and bottom boundaries
	for (int i = 0; i < imax; i++)
	{
		double x = dx * i;

		Psi->mat_2D[i][0] = 1.25 * (2 * x - 0.5 * x * x) - 2.5;
		Psi->mat_2D[i][jmax - 1] = 2.5 - 1.25 * (2 * x - 0.5 * x * x);
	}

	//Left and right boundaries
	for (int j = 0; j < jmax; j++)
	{
		double y = dx * j;
		Psi->mat_2D[0][j] = 10 * y - 2.5;
		Psi->mat_2D[imax - 1][j] = 0;
	}

	//Initial values for internal points
	for (int i = 1; i < imax-1; i++)
		for (int j = 1; j < jmax-1; j++)
			Psi->mat_2D[i][j] = 0.0;
		
	//Copy initial and boundary values into Psi_old
	for (int i = 0; i < imax; i++)
		for (int j = 0; j < jmax; j++)
			Psi_old->mat_2D[i][j] = Psi->mat_2D[i][j];
}

void CWorld::setup()
{
	Psi = new Cmatrix(imax, jmax);
	Psi_old = new Cmatrix(imax, jmax);

	dx = L / (imax - 1);

	set_BC();
}

void CWorld::do_iterations(double tol)
{
	double a = 1.0, b = 1.0, c = 1.0, d = 1.0, e = -4.0, f = 0.0;
	double residave = tol * 10, valtot;
	int cnt = 0;

	while (residave > tol)
	{
		residave = 0.0;
		valtot = 0.0;
		//loop over internal points to do calculation
		for (int i = 1; i < imax - 1; i++)
			for (int j = 1; j < jmax - 1; j++)
			{
				Psi->mat_2D[i][j] = (1.0 / e) * (f - (a * Psi_old->mat_2D[i + 1][j] + b * Psi_old->mat_2D[i - 1][j] + c * Psi_old->mat_2D[i][j + 1] + d * Psi_old->mat_2D[i][j - 1]));
				valtot += fabs(Psi->mat_2D[i][j]);
				residave += fabs(Psi->mat_2D[i][j]- Psi_old->mat_2D[i][j]);
			}

		residave = residave / max(valtot, 1.0e-10);

		if (cnt % 100 == 0)
			cout << cnt << ":\t" << residave << endl;

		//swap matrix pointers - now need to copy data, which is slow
		Cmatrix* temp = Psi;
		Psi = Psi_old;
		Psi_old = temp;

		cnt++;
	}
}

void CWorld::run_world()
{
	setup();

	do_iterations(1.e-6);

	Psi->to_tab_file("output.txt");

	delete Psi;
	delete Psi_old;
}

int main(int argc, char* argv[])
{
	CWorld World;

	World.run_world();
	
	return 0;
}
