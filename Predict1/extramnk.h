#ifndef EXTRAMNK_H
#define EXTRAMNK_H

class ExtraMNK
{
public:
   static double *MNK(double *x, double *y, int n, int k);
   static void PrHodGauss(int n, double **a, double *b);
   static void ObHodGauss(int n, double **a, double *b, double *x);
   static double FExtra(double x, double *c, int k);
   static void MainComputing();
   static double *PolData;
   //static float Coeff
   static double* c;
};

#endif // EXTRAMNK_H
