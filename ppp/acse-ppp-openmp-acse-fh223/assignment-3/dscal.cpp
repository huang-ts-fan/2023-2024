// Scales an array
void dscal(int n, double sa, double sx[], int incx)
{
  if (incx == 1)
  {
    for (int i = 0; i < n; i++)
      sx[i] *= sa;
  }
  else
  {
    for (int j = 0, i = 0; i < n; i++, j += incx)
    {
      sx[j] *= sa;
    }
  }
}
