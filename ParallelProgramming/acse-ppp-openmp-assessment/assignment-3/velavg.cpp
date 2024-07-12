#include <cmath>

// Compute average velocity
double velavg(int npart, double vh[], double vaver, double h, int &count)
{
  double vaverh = vaver * h;
  double vel = 0.0;

  count = 0.0;
  for (int i = 0; i < npart * 3; i += 3)
  {
    double sq = sqrt(vh[i] * vh[i] + vh[i + 1] * vh[i + 1] + vh[i + 2] * vh[i + 2]);
    if (sq > vaverh)
      count++;
    vel += sq;
  }
  vel /= h;

  return (vel);
}
