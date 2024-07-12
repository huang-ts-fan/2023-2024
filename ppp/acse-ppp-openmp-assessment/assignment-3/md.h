#ifndef MD_H
#define MD_H

// Function declarations
void dfill(int, double, double[], int);
void domove(int, double[], double[], double[], double);
void dscal(int, double, double[], int);
void fcc(double[], int, double);
void forces(int, double[], double[], double, double, double &, double &);
double mkekin(int, double[], double[], double, double);
void mxwell(double[], int, double, double);
void prnout(int, double, double, double, double, double, int, int, double);
double velavg(int, double[], double, double, int &);
double secnds(void);

#endif