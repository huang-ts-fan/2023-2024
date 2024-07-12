#define _USE_MATH_DEFINES

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <mpi.h>

using namespace std;

// set up simulation constants
int imax = 301, jmax = 301;
double t_max = 30.0;
double t, t_out = 0.0, dt_out = 0.1, dt;
double y_max = 30.0, x_max = 30.0, dx, dy;
const double f = 2.0, q = 0.002, epsilon = 0.03, D1 = 1.0, D2 = 0.6;

// Write the output for a single time step to file
void grid_to_file(int out, int rank, vector<vector<double> > &C1, vector<vector<double> > &C2, int local_imax, int local_jmax)
{
    // declare file streams
    stringstream fname1, fname2;
    fstream f1, f2;
    fname1 << "./MPI_out_neu/output_C1_" << rank << "_" << out << ".dat";
    f1.open(fname1.str().c_str(), ios_base::out);
    fname2 << "./MPI_out_neu/output_C2_" << rank << "_" << out << ".dat";
    f2.open(fname2.str().c_str(), ios_base::out);
    for (int i = 1; i < local_imax - 1; i++) {
        for (int j = 0; j < local_jmax; j++) {
            f1 << C1[i][j] << "\t";
            f2 << C2[i][j] << "\t";
        }
        f1 << endl;
        f2 << endl;
    }
    f1.close();
    f2.close();
}

// rules for a single time step (Neumann boundary conditions)
void do_iteration_neumann(vector<vector<double> > &C1, vector<vector<double> > &C1_old, vector<vector<double> > &C2, vector<vector<double> > &C2_old, int rank, int size, int local_imax, int local_jmax, MPI_Datatype mpi_custom_type)
{
    // set up MPI communication
    MPI_Request requests[8];
    MPI_Status statuses[8];
    int num_requests = 0;

    // swap pointers to avoid copying data
    C1.swap(C1_old);
    C2.swap(C2_old);

    // define neighbouring ranks
    int up = (rank == 0) ? MPI_PROC_NULL : rank - 1;
    int down = (rank == size - 1) ? MPI_PROC_NULL : rank + 1;

    // Non-blocking communication for boundary rows using custom MPI data types
    MPI_Isend(&C1_old[1][0], 1, mpi_custom_type, up, 0, MPI_COMM_WORLD, &requests[num_requests++]);
    MPI_Irecv(&C1_old[0][0], 1, mpi_custom_type, up, 0, MPI_COMM_WORLD, &requests[num_requests++]);
    MPI_Isend(&C2_old[1][0], 1, mpi_custom_type, up, 1, MPI_COMM_WORLD, &requests[num_requests++]);
    MPI_Irecv(&C2_old[0][0], 1, mpi_custom_type, up, 1, MPI_COMM_WORLD, &requests[num_requests++]);

    MPI_Isend(&C1_old[local_imax - 2][0], 1, mpi_custom_type, down, 0, MPI_COMM_WORLD, &requests[num_requests++]);
    MPI_Irecv(&C1_old[local_imax - 1][0], 1, mpi_custom_type, down, 0, MPI_COMM_WORLD, &requests[num_requests++]);
    MPI_Isend(&C2_old[local_imax - 2][0], 1, mpi_custom_type, down, 1, MPI_COMM_WORLD, &requests[num_requests++]);
    MPI_Irecv(&C2_old[local_imax - 1][0], 1, mpi_custom_type, down, 1, MPI_COMM_WORLD, &requests[num_requests++]);

    // Wait for communication to complete before implementing boundary conditions
    MPI_Waitall(num_requests, requests, statuses);
    
    // Compute new values for internal points
    for (int i = 1; i < local_imax - 1; i++) {
        for (int j = 1; j < local_jmax - 1; j++) {
            C1[i][j] = C1_old[i][j] + dt * ((C1_old[i][j] * (1.0 - C1_old[i][j]) - f * C2_old[i][j] * (C1_old[i][j] - q) / (C1_old[i][j] + q)) / epsilon
                + D1 * ((C1_old[i + 1][j] + C1_old[i - 1][j] - 2.0 * C1_old[i][j]) / (dx * dx) + (C1_old[i][j + 1] + C1_old[i][j - 1] - 2.0 * C1_old[i][j]) / (dy * dy)));

            C2[i][j] = C2_old[i][j] + dt * (C1_old[i][j] - C2_old[i][j]
                + D2 * ((C2_old[i + 1][j] + C2_old[i - 1][j] - 2.0 * C2_old[i][j]) / (dx * dx) + (C2_old[i][j + 1] + C2_old[i][j - 1] - 2.0 * C2_old[i][j]) / (dy * dy)));
        }
    }

    // Implement boundary conditions (Neumann)
    if (rank == 0) {
        for (int j = 0; j < local_jmax; j++) {
            C1[0][j] = C1[1][j];
            C2[0][j] = C2[1][j];
        }
    }
    if (rank == size - 1) {
        for (int j = 0; j < local_jmax; j++) {
            C1[local_imax - 1][j] = C1[local_imax - 2][j];
            C2[local_imax - 1][j] = C2[local_imax - 2][j];
        }
    }

    for (int i = 1; i < local_imax - 1; i++) {
        C1[i][0] = C1[i][1];
        C1[i][local_jmax - 1] = C1[i][local_jmax - 2];
        C2[i][0] = C2[i][1];
        C2[i][local_jmax - 1] = C2[i][local_jmax - 2];
    }

    t += dt;
}

// Calculate the time step and grid spacing
void calc_constants()
{
    dx = x_max / ((double)imax - 1);
    dy = y_max / ((double)jmax - 1);
    t = 0.0;
    dt = 0.1 * pow(min(dx, dy), 2.0) / (2.0 * max(D1, D2));
    cout << "dt = " << dt << " dx = " << dx << " dy = " << dy << endl;
}

// Set up the initial data profile
void setup_data_profile(vector<vector<double> > &C1, vector<vector<double> > &C2, int local_imax, int local_jmax, int rank, int size)
{
    // use the rank to determine the global x and y coordinates
    double global_x, global_y, origin_x = x_max / 2.0, origin_y = y_max / 2.0;

    int global_start = rank * (imax / size);
    int global_end = global_start + local_imax - 2;

    for (int i = 1; i < local_imax - 1; i++) {
        int global_i = global_start + i - 1;
        for (int j = 0; j < local_jmax; j++) {
            global_x = global_i * dx;
            global_y = j * dy;
            double angle = atan2(global_y - origin_y, global_x - origin_x);

            if (angle > 0.0 and angle < 0.5)
                C1[i][j] = 0.8;
            else
                C1[i][j] = q * (f + 1) / (f - 1);

            C2[i][j] = q * (f + 1) / (f - 1) + angle / (8 * M_PI * f);
        }
    }
}

int main(int argc, char** argv)
{
    // Initialize MPI
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // start timer
    double start = MPI_Wtime();

    int local_imax = imax / size + 2; // Adding 2 for the ghost rows
    int local_jmax = jmax;

    vector<vector<double> > C1(local_imax, vector<double>(local_jmax));
    vector<vector<double> > C1_old(local_imax, vector<double>(local_jmax));
    vector<vector<double> > C2(local_imax, vector<double>(local_jmax));
    vector<vector<double> > C2_old(local_imax, vector<double>(local_jmax));

    // Define custom MPI data types (for sending rows) use MPI_Type_create_struct
    MPI_Datatype mpi_custom_type;
    int blocklengths[1] = {local_jmax};
    MPI_Aint displacements[1] = {0};
    MPI_Datatype types[1] = {MPI_DOUBLE};
    MPI_Aint lb, extent;
    MPI_Type_get_extent(MPI_DOUBLE, &lb, &extent);
    displacements[0] = lb;
    MPI_Type_create_struct(1, blocklengths, displacements, types, &mpi_custom_type);
    MPI_Type_commit(&mpi_custom_type);

    int out_cnt = 0, it = 0;

    calc_constants();
    setup_data_profile(C1, C2, local_imax, local_jmax, rank, size);
    grid_to_file(out_cnt, rank, C1, C2, local_imax, local_jmax);
    out_cnt++;
    t_out += dt_out;

    // Main loop
    while (t < t_max)
    {
        // Perform iteration
        do_iteration_neumann(C1, C1_old, C2, C2_old, rank, size, local_imax, local_jmax, mpi_custom_type);

        if (t_out <= t)
        {
            // Output to file
            if (rank == 0) {
                cout << "output: " << out_cnt << "\tt: " << t << "\titeration: " << it << "\tmid " << C1[local_imax / 2][local_jmax / 2] << endl;
            }
            grid_to_file(out_cnt, rank, C1, C2, local_imax, local_jmax);
            out_cnt++;
            t_out += dt_out;
        }

        it++;
    }

    // Stop timer
    double end = MPI_Wtime();

    // Output time taken
    if (rank == 0) {
        cout << "Time taken: " << end - start << " seconds" << endl;
    }

    // Clean up MPI data types
    MPI_Type_free(&mpi_custom_type);
    MPI_Finalize();

    return 0;
}
