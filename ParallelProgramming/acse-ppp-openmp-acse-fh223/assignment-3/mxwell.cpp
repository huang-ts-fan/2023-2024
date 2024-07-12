#include <cmath>
#include <random>

// Sample Maxwell distribution at temperature tref
void mxwell(double vh[], int n3, double h, double tref)
{
  int npart = n3 / 3;
  double r, tscale, v1, v2, s, ekin = 0.0, sp = 0.0, sc;

  // Create a random device and seed it
  std::random_device rd;
  std::mt19937 gen(12345);

  // Create a uniform_real_distribution
  std::uniform_real_distribution<> dis(-1.0, 1.0);

  tscale = 16.0 / ((double)npart - 1.0);

  for (int i = 0; i < n3; i += 2)
  {
    s = 2.0;
    while (s >= 1.0)
    {
      v1 = dis(gen);
      v2 = dis(gen);
      s = v1 * v1 + v2 * v2;
    }
    r = sqrt(-2.0 * log(s) / s);
    vh[i] = v1 * r;
    vh[i + 1] = v2 * r;
  }

  for (int i = 0; i < n3; i += 3)
    sp += vh[i];
  sp /= (double)npart;

  for (int i = 0; i < n3; i += 3)
  {
    vh[i] -= sp;
    ekin += vh[i] * vh[i];
  }

  sp = 0.0;
  for (int i = 1; i < n3; i += 3)
    sp += vh[i];
  sp /= (double)npart;

  for (int i = 1; i < n3; i += 3)
  {
    vh[i] -= sp;
    ekin += vh[i] * vh[i];
  }

  sp = 0.0;
  for (int i = 2; i < n3; i += 3)
    sp += vh[i];
  sp /= (double)npart;

  for (int i = 2; i < n3; i += 3)
  {
    vh[i] -= sp;
    ekin += vh[i] * vh[i];
  }

  sc = h * sqrt(tref / (tscale * ekin));
  for (int i = 0; i < n3; i++)
    vh[i] *= sc;
}
