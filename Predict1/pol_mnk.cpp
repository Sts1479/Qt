#include "pol_mnk.h"

#include<math.h>
#include<iostream>
#define len 50//степень аппроксиамации,размер матрицы& ...;
/*******************************Тестовая функция***************************/
double Tfunc(double a) //Паробола;
 {return (a*a);}
/***************************************************************************/
int i,j,k;         //для организации циклов;
int n;             //степень аппроксимации МНСП;
int m;             //Число разбиений ,m+1 число точек на [A,B];
double a[len][len+1];      //решаемая система - расширенная матрица;
double A,B;            //орезок-[A,B];
double c0[len];        //массив коэффициентов;
double cnst,h,x;
//double Fn(double x,int n);//возращает знач.МНСП в точке X,n-степень апроксимации;
//void pogrech();
//void ipMatr();     //ввод матрицы;
//void opMatr();     //вывод матрицы;

void Pol_MNK::Gauss()
{
double aa,bb;
Pol_MNK::IpMatr();
for(Pol_MNK::OpMatr(),k=0;k<=n;k++)        //прямой ход метода Гаусса;
 {for(aa=fabs(a[k][k]),i=k,j=k+1;j<=n;j++)//поиск макс. ел-та;
    if(fabs(a[j][k])>aa){i=j;aa=fabs(a[j][k]);};
    if(aa<0)
      {printf("Система не имеет единственного решения!!!");
       getch();

      }
  for(j=k;(j<=n+1)&&(i!=k);j++)       //перестановка i-ой строки;
      {bb=a[k][j];
       a[k][j]=a[i][j];
       a[i][j]=bb;
      }
  for(aa=a[k][k],a[k][k]=1,j=k+1;j<=n+1;j++)//преобразование ведущей строки;
     a[k][j]=a[k][j]/aa;
  for(i=k+1;i<=n;i++)                   //метод Гаусса;
    for(bb=a[i][k],a[i][k]=0,j=k+1;(j<=n+1)&&(bb!=0);j++)
     a[i][j]=a[i][j]-bb*a[k][j];
 }
for(Pol_MNK::OpMatr(),i=n;i>=0;c0[i]=aa,i--)     //Обратный ход метода;
   for(aa=a[i][n+1],j=n;j>=i+1;j--)
      aa=aa-a[i][j]*c0[j];
for(i=0;i<=n;printf("c%d=%10.15lf\n",i,c0[i]),i++);//вывод коэффициентов;
Pol_MNK::Error();
system("PAUSE");

}
void Pol_MNK::IpMatr()
 {
 printf("Определите степень аппроксимации MNK\n n=");scanf("%d",&n);
 printf("Задайте отрезок [A,B]:\n A=");scanf("%lf",&A);
 printf(" B=");scanf("%lf",&B);
 cnst=B-A;
 printf("Введите число разбиений отрезка[A,B](min=1)\n m=");
 scanf("%d",&m);
 h=cnst/m;          //шаг разбиения;
 for(i=0;i<=n;i++)
    for(j=0;j<=n+1;j++)     //формирование a[i][j];
       {if(j<=n) a[i][j]=(pow(B,i+j+1)-pow(A,i+j+1))/(cnst*(i+j+1));
    else            //формирование B[i];
//поиск интеграла на дискретном множеств;
     {for(a[i][j]=0,x=A,k=0;(k<=m);k++,x=x+h)//формирование B[i];
         {a[i][j]=a[i][j]+Tfunc(x)*pow(x,i);}//сумма;
      a[i][j]=(a[i][j])/(m+1);       //нормировка;
     }

       }
 }

void Pol_MNK::OpMatr()
 {for(i=0;i<=n;i++,printf("\n"))
     for(j=0;j<=n+1;j++)
       {if(j==n+1)printf("=%10.6lf",a[i][j]);else printf(" %10.7lf",a[i][j]); };
  printf("\n");
 }

double Pol_MNK::ExtraFunc(double x,int n)
 {double F=0;
  for(i=0;i<=n;i++)
   {F=F+c0[i]*pow(x,i);}
  return F;
 }

void Pol_MNK::Error()
 {double max,p,ps,del;
  max=fabs(Tfunc(A)-Fn(A,n));
  ps=pow(max,2);
  del=pow(Tfunc(A),2);
  for(x=A+h;x<=B;x+=h)
    {p=fabs(Tfunc(x)-Fn(x,n));
     if(p>max)max=p;
     ps=ps+pow(p,2);
     del=del+pow(Tfunc(x),2);
    }
  printf("\Погрешность приближения=%10.10lf\n",sqrt(ps/del));
  ps=sqrt(ps/(m+1));
  printf("Средняя практическая погрешность=%10.10lf\n",ps);
  printf("Maxимальная практическая погрешность=%10.10lf\n",max);
 }


