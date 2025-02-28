#include <iostream>
#include <cmath>
#include <omp.h>

#include "md.h"

#define mm 15
#define npart 4 * mm *mm *mm

// Main program : Molecular Dynamics simulation.
int main()
{
  double x[npart * 3], vh[npart * 3], f[npart * 3];
  double ekin;
  double vel;
  double sc;
  double epot=0.0, vir=0.0;
  int count=0;

  // Parameter definitions
  double den = 0.83134;
  double side = pow((double)npart / den, 0.3333333);
  double tref = 0.722;
  double rcoff = (double)mm / 4.0;
  double h = 0.064;
  int irep = 10;
  int istop = 20;
  int iprint = 5;
  int movemx = 20;

  double a = side / (double)mm;
  double hsq = h * h;
  double hsq2 = hsq * 0.5;
  double tscale = 16.0 / ((double)npart - 1.0);
  double vaver = 1.13 * sqrt(tref / 24.0);

  // Initial output
  printf(" Molecular Dynamics Simulation example program\n");
  printf(" ---------------------------------------------\n");
  printf(" number of particles is ............ %6d\n", npart);
  printf(" side length of the box is ......... %13.6f\n", side);
  printf(" cut off is ........................ %13.6f\n", rcoff);
  printf(" reduced temperature is ............ %13.6f\n", tref);
  printf(" basic timestep is ................. %13.6f\n", h);
  printf(" temperature scale interval ........ %6d\n", irep);
  printf(" stop scaling at move .............. %6d\n", istop);
  printf(" print interval .................... %6d\n", iprint);
  printf(" total no. of steps ................ %6d\n", movemx);

  double start = omp_get_wtime();

  // Generate fcc lattice for atoms inside box
  fcc(x, mm, a);

  // Initialise velocities and forces (which are zero in fcc positions)
  mxwell(vh, 3 * npart, h, tref);
  dfill(3 * npart, 0.0, f, 1);

  // Start of md
  printf("\n    i       ke         pe            e         temp   "
         "   pres      vel      rp\n  -----  ----------  ----------"
         "  ----------  --------  --------  --------  ----\n");

  for (int move = 1; move <= movemx; move++)
  {
    #pragma omp single
    {
      // Move the particles and partially update velocities
      domove(3 * npart, x, vh, f, side);
    }
    
    // Compute forces in the new positions and accumulate the virial
    // and potential energy.
    forces(npart, x, f, side, rcoff, epot, vir);

    #pragma omp single
    {
      
      // Scale forces, complete update of velocities and compute k.e.
      ekin = mkekin(npart, f, vh, hsq2, hsq);

      // Average the velocity and temperature scale if desired
      vel = velavg(npart, vh, vaver, h, count);
      if (move < istop && fmod(move, irep) == 0)
      {
        sc = sqrt(tref / (tscale * ekin));
        dscal(3 * npart, sc, vh, 1);
        ekin = tref / tscale; 
      }

      // Sum to get full potential energy and virial
      if (fmod(move, iprint) == 0)
        prnout(move, ekin, epot, tscale, vir, vel, count, npart, den);
    }
  }

  double end = omp_get_wtime();
  //printf("Time taken: %f\n", end - start);
  
}
