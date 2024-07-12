// Generate fcc lattice for atoms inside the box
void fcc(double x[], int mm, double a)
{
  int ijk = 0;
  for (int lg = 0; lg < 2; lg++)
    for (int i = 0; i < mm; i++)
      for (int j = 0; j < mm; j++)
        for (int k = 0; k < mm; k++, ijk += 3)
        {
          x[ijk] = i * a + lg * a * 0.5;
          x[ijk + 1] = j * a + lg * a * 0.5;
          x[ijk + 2] = k * a;
        }

  for (int lg = 1; lg < 3; lg++)
    for (int i = 0; i < mm; i++)
      for (int j = 0; j < mm; j++)
        for (int k = 0; k < mm; k++, ijk += 3)
        {
          x[ijk] = i * a + (2 - lg) * a * 0.5;
          x[ijk + 1] = j * a + (lg - 1) * a * 0.5;
          x[ijk + 2] = k * a + a * 0.5;
        }
}
