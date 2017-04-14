#include "mathmethods.h"
#include "fileop.h"
#include <QDebug>
int MathMethods::p[11];
//double MathMethods::PI=3.1415926535;
int MathMethods::flag;
double MathMethods::om;
void MathMethods::PiM()
{
for (int i=0;i<10;i++) p[i+1]=i;
//return p;
}

double MathMethods::FUNC(double x)
{
    if (!flag) return (F(x)*cos(om*x)); //for an
    else return (F(x)*sin(om*x)); //for bn
}
double MathMethods::F(double x)
{
    if (x<-PI) return 0.0;
    else if (x<-PI/2) return PI/4;
    else if (x<=PI) return -PI/4;
    else return 0.0;
}
/*
The Fourier series  of a periodic discreet function F(x)
                   n=inf.
       F(x) = a0 + Sum ( an cos(2 n pi/T x) + bn sin(2 n pi/T x)
                   n=1
*/
void MathMethods::DiscreteFourierHn(int ndata, double *X, double *Y, int n, double *a, double *b)
{
    int i;
      double xi,T,om,wa,wb,wc,wd,wg,wh,wi,wl,wm,wn,wp;
      T=X[ndata]-X[1]; xi=(X[ndata]+X[1])/2;
      om = 2*PI*n/T; *a=0; *b=0;
      for (i=1; i<ndata; i++) {
        wa=X[i]; wb=X[i+1];
        wc=Y[i]; wd=Y[i+1];
        if (wa != wb)  {
          wg = (wd-wc)/(wb-wa);
          wh = om*(wa-xi); wi=om*(wb-xi);
          if (n==0)
            *a += (wb-wa)*(wc+wg/2*(wb-wa));
          else {
            wl = cos(wh); wm = sin(wh);
            wn = cos(wi); wp = sin(wi);
            *a += wg/om*(wn-wl) + wd*wp - wc*wm;
            *b += wg/om*(wp-wm) - wd*wn + wc*wl;
          }
        }
      }
      *a /= T; *b /= T;
      if (n != 0)  {
        *a *= 2/om; *b *= 2/om;
      }
}
/******************************************************
 * Integral of a function FUNC(X) by Romberg's method  *
 * --------------------------------------------------- *
 * INPUTS:                                             *
 *          a      begin value of x variable           *
 *          b      end value of x variable             *
 *       prec      desired precision                   *
 *    itermin      minimum number of ietrations        *
 *    itermax      maximum0 number of iterations        *
 *                                                     *
 * OUTPUTS:                                            *
 *    obtprec      obtained precision for integral     *
 *          n      number of iterations done           *
 *                                                     *
 * RETURNED VALUE  the integral of FUNC(X) from a to b *
 *                                                     *
 ******************************************************/
 double MathMethods::RombergIntegral(double a,double b,double prec, double *obtprec, int *n, int itermin, int itermax)
 {
   int    i,j;
   double pas,r,s,ta;
   double t[MAXITER+1][MAXITER+1];
   if (itermax>MAXITER) itermax=MAXITER;
   r = FUNC(a);
   ta = (r + FUNC(b)) / 2;
   *n=0;
   pas=b-a;
   t[0][0]=ta*pas;
   do {
     *n = *n + 1;
     pas = pas/2;
     s=ta;
     for (i=1; i<pow(2,*n); i++)
       s += FUNC(a+pas*i);
     t[0][*n]=s*pas;
     r=1;
     for (i=1; i<*n+1; i++) {
       r=r*4;
       j=*n-i;
       t[i][j]=(r*t[i-1][j+1] - t[i-1][j])/(r-1);
     }
     *obtprec = fabs(t[*n][0] - t[*n-1][0]);
     if (*n>=itermax) return t[*n][0];
   } while (*obtprec >prec || *n<itermin);
   return t[*n][0];
 }


 /***************************************************************
   * Calculate the Fourier harmonic #n of a periodic function F(x)*
   * analytically defined.                                        *
   * ------------------------------------------------------------ *
   * Inputs:                                                      *
   *            t1   : -period/2                                  *
   *            t2   : period/2                                   *
   *            n    : order of harmonic                          *
   *                                                              *
   * Outputs:                                                     *
   *            a    : coefficient an of the Fourier series.      *
   *            b:   : coefficient bn of the Fourier series.      *

   Note:  When a periodic function f(x), of period T, can be developped
          in a Fourier series, this one is unique:
                      n=inf.
  MathMethods::MainComputing()
          F(x) = a0 + Sum ( an cos(2 n pi/T x) + bn sin(2 n pi/T x)
                      n=1
          (b0 is always zero).

          The coefficients an, bn are given by:
                       T/2
              a0 = 1/T Sum (f(x) dx)
                       -T/2w
                       T/2
              an = 2/T Sum (f(x) cos(2npi/T x) dx)
                       -T/2
                       T/2
              an = 2/T Sum (f(x) sin(2npi/T x) dx)
                       -T/2
          Here, the integrals are calculated by the Romberg method.
   --------------------------------------------------------------------*/
 void MathMethods::AnalyticFourierHn(double t1,double t2, int n, double *a, double *b)  {
   double T,precision,temp;
   int itmax,niter;
   T=fabs(t2-t1);
   om=2.0*PI*n/T;
   precision=1e-10; itmax=15;
   flag=0; // calculate an
   *a=RombergIntegral(t1,t2,precision,&temp,&niter,5,itmax)*2/T;
   flag=1; // calculate bn
   *b=RombergIntegral(t1,t2,precision,&temp,&niter,5,itmax)*2/T;
   if (n==0) *a=*a/2;
 }


// void DFT(const double inreal[],const double inimag[],double outreal[],double outimag[], int n)
// {
//     int k;
//     for (k=0;k<n;t++)
//     {
//     double sumreal=0;
//     double sumimag=0;
//     for (int t=0;t<n;t++)
//     {
//         double angle=2*PI*t*k/n;
//         sumreal+=inreal[t]*cos(angle)+inimagp[t]*sin(angle);
//         sumimag+=-inreal[t]*sin(angle)+inimag[t]*cos(angle);
//     }
//     outreal[k]=sumreal;
//     outimag[k]=sumimag;
//     }
// }


//float MathMethods::DFT(float InSig[], int N) //
//{
//    float Re,Im,Arg,A,F,Fr;
//    float summa_Re=0;
//    float summa_Im=0;
//    for (int k=0;k<N;k++)
//    {
//        for (int n=0;n<N;n++)
//        {
//            Arg=2*PI*n*k/N;
//            Re=cos(Arg)*InSig[n];
//            Im=sin(Arg)*InSig[n];
//            summa_Re=summa_Re+Re;
//            summa_Im=summa_Im+Im;
//        }
//        summa_Re=summa_Re/(float)N;
//        summa_Im=summa_Im/(float)N;
//        A=sqrt(summa_Re*summa_Re+summa_Im*summa_Im);
//        F=atan(summa_Im/summa_Re);
//        Fr=(N-1)*k;
//    }
//    return A;
//}

MathMethods::DFTData MathMethods::valDFTData;

void MathMethods::DFT(float InSig[], int N)
{
    valDFTData.Ampl=new float[N];
    valDFTData.Phase=new float[N];
    valDFTData.ReSpec=new float[N];
    valDFTData.ImSpec=new float[N];
    float Re,Im,Arg,A,F,Fr;
    float summa_Re=0;
    float summa_Im=0;
    for (int k=0;k<N;k++)
    {
        for (int n=0;n<N;n++)
        {
            Arg=2*PI*n*k/N;
            Re=cos(Arg)*InSig[n];
            Im=sin(Arg)*InSig[n];
            summa_Re=summa_Re+Re;
            summa_Im=summa_Im+Im;
        }
       summa_Re=summa_Re/N;
       summa_Im=summa_Im/N;
        valDFTData.Ampl[k]=2*sqrt((summa_Re*summa_Re)+(summa_Im*summa_Im));
        valDFTData.Phase[k]=atan(summa_Im/summa_Re);
        valDFTData.ReSpec[k]=summa_Re;
        valDFTData.ImSpec[k]=summa_Im;
        Fr=(N-1)*k;
    }
}

MathMethods::IDFTData MathMethods::valIDFTData;

void MathMethods::IDFT(float ReSpec[],float ImSpec[], int K, int N)
{
    valIDFTData.IAmpl=new float[K];
    float Arg,X;
    float summa_X=0,Im=0,Re=0;
    float summa_Re=0;
    float summa_Im=0;
    for (int k=0;k<K;k++)
    {
        for (int n=0;n<N;n++)
        {
            Arg=2*PI*k*n/N;

            X=ReSpec[n]*cos(-Arg)+ImSpec[n]*sin(-Arg);
             summa_X=summa_X+X;
//             summa_Re=ReSpec[n]*cos(Arg)-ImSpec[n]*sin(Arg);
//             summa_Im=ImSpec[n]*cos(Arg)+ReSpec[n]*sin(Arg);
//             summa_Im=summa_Im+Im;
//             summa_Re=summa_Re+Re;
        }
        valIDFTData.IAmpl[k]=summa_X;
        summa_Im=0;summa_Re=0;summa_X=0;
    }
}

void MathMethods::FourierSeriesD(float InSig[], int N, int Harm)
{
    for (int k=0;k<Harm;k++)
    {
        for (int n=0;n<N;n++)
        {
             //Arg=2*PI*n*k/N;
             //A=cos(Arg)*InSig[n];
        }
    }
}




void MathMethods::MainComputing()
{
    int NLengthData=450;
    int NLengthBuff=200;
    FileOp::ReadFile(FileOp::existFileNameOpen);

   float INData[FileOp::NDataSize];
   float INBuff[100];
   for (int i=0;i<FileOp::NDataSize;i++) {
       INData[i]=FileOp::valRData.InSignalVect.at(i);
        qDebug() << FileOp::valRData.InSignalVect.at(i);
   }
   //timer.start();
    MathMethods::DFT(INData,NLengthBuff);
    MathMethods::IDFT(MathMethods::valDFTData.ReSpec,MathMethods::valDFTData.ImSpec,FileOp::NDataSize,NLengthBuff);
    for (int i=0;i<FileOp::NDataSize;i++) {
        qDebug()<<MathMethods::valIDFTData.IAmpl[i]<<"     "<<i;
    }
   FileOp::WriteFile(FileOp::existFileNameWrite);
}
