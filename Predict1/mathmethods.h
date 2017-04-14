#ifndef MATHMETHODS_H
#define MATHMETHODS_H
#include <math.h>
#define MAXITER 15
#include "qvector.h"

class MathMethods
{
public:
    static struct FourierD
    {
        float A;
        float B;
    }valFourierD;

    static struct DFTData
    {
        int NSize;
        float *Ampl;
        float *Phase;
        float *Freq;
        float *ReSpec;
        float *ImSpec;
    }valDFTData;

    static struct IDFTData
    {
        int INSize;
        float *IAmpl;
        float *IPhase;
        float *IFreq;
    }valIDFTData;


    static struct RVect
    {
        QVector<double> VectSignal;

    }valRVect;

    //
    static const double PI=3.1415926535;
    static int flag;
    static double om;
    static int p[11];
    static void PiM();
    static double F(double x);
    static double FUNC(double x);
    static void DiscreteFourierHn(int ndata,double *X,double *Y,int n,double *a, double *b);
    static double RombergIntegral(double a, double b, double prec, double *obtprec, int *n,int itermin,int itermax);
    static void AnalyticFourierHn(double t1,double t2,int n,double *a,double *b);
    //static void DFT(const double inreal[],const double inimag[],double outreal[],double outimag[], int n);
    static void DFT(float InSig[], int N);
    static void FourierSeriesD(float InSig[], int N, int Harm);
    static void IDFT(float ReSpec[],float ImSpec[], int K, int N);
    static void PeriodCondWindow(int WLength);
    static void MainComputing();
    static void Gauss(int i,int j, int n,int m);
};

#endif // MATHMETHODS_H
