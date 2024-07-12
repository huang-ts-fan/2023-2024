#include <vector>
#include <omp.h>

void forces(int npart, double x[], double f[], double side, double rcoff, double &epot, double &vir)
{
  epot = 0.0;
  vir = 0.0;

  double sideh = 0.5 * side;
  double rcoffs = rcoff * rcoff;

  // "epot" and "vir" are reduction variables
  // add schedule will not significantly improve performance (in my test even slower)
  // but it run faster by using dynamic schedule
  #pragma omp parallel for reduction(+ : epot, vir) schedule(dynamic)
  for (int i = 0; i < npart * 3; i += 3) 
  {
      double fxi = 0.0;
      double fyi = 0.0;
      double fzi = 0.0;

      for (int j = i + 3; j < npart * 3; j += 3)
      {
        double xx = x[i] - x[j];
        double yy = x[i + 1] - x[j + 1];
        double zz = x[i + 2] - x[j + 2];
        if (xx < -sideh)
          xx += side;
        if (xx > sideh)
          xx -= side;
        if (yy < -sideh)
          yy += side;
        if (yy > sideh)
          yy -= side;
        if (zz < -sideh)
          zz += side;
        if (zz > sideh)
          zz -= side;
        double rd = xx * xx + yy * yy + zz * zz;

        if (rd <= rcoffs)
        {
          double rrd = 1.0 / rd;
          double rrd3 = rrd * rrd * rrd;
          double rrd6 = rrd3 * rrd3;
          double r148 = rrd6 * rrd - 0.5 * rrd3 * rrd;

          epot += rrd6 - rrd3;
          vir -= rd * r148;

          xx *= r148;
          yy *= r148;
          zz *= r148;

          fxi += xx;
          fyi += yy;
          fzi += zz;

          // Use "critical" to make sure that the update of f[j] is atomic is slower than "atomic"
          #pragma omp atomic
          f[j] -= xx;
          #pragma omp atomic
          f[j + 1] -= yy;
          #pragma omp atomic
          f[j + 2] -= zz;
          
        }
      }

      // Use "critical" to make sure that the update of f[i] is atomic is slower than "atomic"
      #pragma omp atomic
      f[i] += fxi;
      #pragma omp atomic
      f[i + 1] += fyi;
      #pragma omp atomic
      f[i + 2] += fzi;
      
      
    }
}