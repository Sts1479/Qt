#include "extramnk.h"
#include "fileop.h"
#include <math.h>
#include <QDebug>

double* ExtraMNK::c = NULL;

double *ExtraMNK::PolData;
double * ExtraMNK::MNK(double *x, double *y, int n, int k)
{
    double **a = new double *[k];
    double *b  = new double [k];
    c  = new double [k];
    for(int m=0,i,j; m < k; m++)
    {
        a[m]=new double[k];
        for(j=0; j<k; j++)
        {
            a[m][j]=0;
            for(i=0; i<n;i++)
                a[m][j]+=pow(x[i],m+j);
        }
        b[m]=0;
        for(i=0; i<n; i++)
            b[m]+=pow(x[i],m)*y[i];
    }
    ExtraMNK::PrHodGauss(k,a,b);
    ExtraMNK::ObHodGauss(k,a,b,c);
    return c;
}

void ExtraMNK::PrHodGauss(int n, double **a, double *b)
{
    double v;
    for(int k=0,i,j,im; k<n-1; k++)
    {
        im=k;
        for(i=k+1; i<n; i++)
        {
            if(fabs(a[im][k]) < fabs(a[i][k]))
            {im=i;}}
        if(im!=k)
        {for(j=0; j<n; j++)
            {v=a[im][j];
            a[im][j]=a[k][j];
            a[k][j]=v;}
            v=b[im];
            b[im]=b[k];
            b[k]=v;}
        for(i=k + 1; i<n; i++)
        {
            v=a[i][k]/a[k][k];
            a[i][k]=0;
            b[i]=b[i]-v*b[k];
            for(j=k+1; j<n; j++)
            {a[i][j]=a[i][j]-v*a[k][j];}}}}

void ExtraMNK::ObHodGauss(int n, double **a, double *b, double *x)
{
    double s=0;
    x[n-1]=b[n-1]/a[n-1][n-1];
    for(int i=n-2,j; 0<=i; i--)
    {   s=0;
        for(j=i+1; j<n; j++)
        {       s=s+a[i][j]*x[j];}
        x[i]=(b[i]-s)/a[i][i];
    }
}

double ExtraMNK::FExtra(double x, double *c, int k)
{
    double RetVal=0;
    for (int i=0; i<k; i++)
    {
    RetVal+=c[i]*pow(x,i);
   // qDebug()<<c[i]<<"     "<<" ";
    }
    return RetVal;
}
void ExtraMNK::MainComputing()
{

   FileOp::ReadFile(FileOp::existFileNameOpen);
   ExtraMNK::PolData=new double [FileOp::NDataSize];
   int NLengthBuff=8;
   double *CPol;
   int PolOrder=8;
   int ExtraPoints=0;
   //double Polinom[FileOp::NDataSize-NLengthBuff];
   double Polinom;
   double INDataY[FileOp::NDataSize];
   double INDataX[FileOp::NDataSize];
   //double ExtraMNK::PolData[FileOp::NDataSize];
   double BuffX[NLengthBuff],BuffY[NLengthBuff],IntBuffY,meanY;
   for (int i=0;i<FileOp::NDataSize;i++) {
       INDataY[i]=FileOp::valRData.InSignalVect.at(i);
       INDataX[i]=(double)i-1;
       //qDebug() << FileOp::valRData.InSignalVect.at(i);
   }
   //timer.start();
   for (int i=0;i<FileOp::NDataSize-NLengthBuff-1;i++)
   {
       for (int j=0;j<NLengthBuff;j++)
       {
        IntBuffY=INDataY[i+j]+IntBuffY;
        qDebug() << i << "";
       }

       meanY=IntBuffY*NLengthBuff;IntBuffY=0;

//       if (i<NLengthBuff)
//       {
//           for (int j=0;j<NLengthBuff;j++) ExtraMNK::PolData[i]=INDataY[i];
//        //   qDebug()<<Polinom<<"     "<<" ";
//       }
//       else
//       {
//           if (ExtraPoints>2)
//           {
//       for (int j=0;j<NLengthBuff;j++) BuffX[j]=INDataX[i+j-NLengthBuff+1];
//       for (int j=0;j<NLengthBuff;j++) BuffY[j]=INDataY[i+j-NLengthBuff+1];
//    CPol=ExtraMNK::MNK(BuffX,BuffY,NLengthBuff,PolOrder);
//    ExtraPoints=0;
//           }
//           ++ExtraPoints;
//    Polinom=ExtraMNK::FExtra(i,CPol,PolOrder);
//    if (abs(Polinom)>100) Polinom=Polinom/1000;
//    ExtraMNK::PolData[i]=Polinom;
//   }
       for (int j=0;j<NLengthBuff;j++) BuffX[j]=INDataX[i+j-NLengthBuff+1];
       for (int j=0;j<NLengthBuff;j++) BuffY[j]=INDataY[i+j-NLengthBuff+1];
    CPol=ExtraMNK::MNK(BuffX,BuffY,NLengthBuff,PolOrder);
    Polinom=ExtraMNK::FExtra(i,CPol,PolOrder);
    ExtraMNK::PolData[i]=Polinom;
   //  qDebug()<<Polinom<<"  Polinom   "<<" ";
    qDebug()<<meanY<<"     "<<" ";

   }

    //MathMethods::DFT(INData,NLengthBuff);
    //MathMethods::IDFT(MathMethods::valDFTData.ReSpec,MathMethods::valDFTData.ImSpec,FileOp::NDataSize,NLengthBuff);
    //for (int i=0;i<FileOp::NDataSize-NLengthBuff;i++) {
  //  }

   FileOp::WriteFile(FileOp::existFileNameWrite);
}
