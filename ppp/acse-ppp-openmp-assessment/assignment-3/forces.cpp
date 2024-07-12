#include <vector>

void forces(int npart, double x[], double f[], double side, double rcoff, double &epot, double &vir)
{
  epot = 0.0;
  vir = 0.0;

  double sideh = 0.5 * side;
  double rcoffs = rcoff * rcoff;

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

          f[j] -= xx;
          f[j + 1] -= yy;
          f[j + 2] -= zz;
        }
      }

      f[i] += fxi;
      f[i + 1] += fyi;
      f[i + 2] += fzi;
    }
}