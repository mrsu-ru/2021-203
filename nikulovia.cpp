#include "nikulovia.h"

/**
 * Введение в дисциплину
 */
void nikulovia::lab1()
{
  cout << "hello world!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void nikulovia::lab2()
{
 int mx;
    for (int i=0; i<N; i++) 
    {
        mx=0;
        for (int j=0; j<N; j++)
            if (abs(A[mx][i])<abs(A[j][i])) 
                mx=j;
        swap(A[i], A[mx]);
        swap(b[i], b[mx]);
        for (int j=i+1; j<N; j++) 
        {
            double ft=A[j][i]/A[i][i];
            for (int k=i+1; k<N; k++)
                A[j][k]=A[j][k]-ft*A[i][k];
            b[j]=b[j]-ft*b[i];
            A[j][i]=0;
        }
    }
    
    
    double dl;
    for(int i=0; i<N; i++)
    {
        dl = A[i][i];
        for(int j=0; j<N; j++)
            A[i][j]=A[i][j]/dl;
        b[i]=b[i]/dl;
    }
    
    
    for (int i=N-1; i>=0; i--)
    {
        x[i]=b[i];
        for (int j=i+1; j<N; j++) 
            x[i]=x[i]-A[i][j]*x[j];
    }
}



/**
 * Метод прогонки
 */
void nikulovia::lab3()
{
int i;
    double al[N];
    double bt[N];

    al[0] = -A[0][1] / A[0][0];
    bt[0] = b[0] / A[0][0];
  
    for (i = 1; i < N; i++) 
    {
        al[i] = -A[i][i + 1] / (A[i][i] + A[i][i - 1] * al[i - 1]);
        bt[i] = (b[i] - A[i][i - 1] * bt[i - 1]) / (A[i][i] + A[i][i - 1] * al[i - 1]);
    }
    x[N - 1] = bt[N - 1];
  
    for (i = N - 2; i > -1; i--) 
    {
        x[i] = bt[i] + al[i] * x[i + 1];
    }
}



/**
 * Метод Холецкого
 */
void nikulovia::lab4()
{
      double* D = new double[N];
    double** S = new double*[N];
    double sds = 0;
  
 for(int i = 0; i < N; i++)
 {
        for(int j = 0; j < N; j++)
            if(A[i][j] != A[j][i]) 
              return;
    }
  
  
    for(int i = 0; i < N; i++) 
      S[i] = new double[N];
    for(int i = 0; i < N; i++)
    {
        sds = 0;
        for(int kd = 0; kd < i; kd++) 
          sds += S[kd][i] * D[kd] * S[kd][i];
        if(A[i][i] - sds < 0) 
          D[i] = -1;
        else 
          D[i] = 1;
        S[i][i] = sqrt(fabs(A[i][i] - sds));
        for(int j = i + 1; j < N; j++)
        {
            sds = 0;
            for(int k = 0; k < j; k++) sds += S[k][i] * D[k] * S[k][j];
            S[i][j] = (A[i][j] - sds) / (S[i][i] * D[i]);
        }
    }
  
    double* y = new double[N];
    for(int i = 0; i < N; i++) 
    {
        y[i] = b[i];
        for (int j = 0; j < i; j++) y[i] -= S[j][i] * D[j] * y[j];
        y[i] /= S[i][i] * D[i];
    }
    for(int i = N - 1; i >= 0; i--)
    {
        for(int j = i + 1; j < N; j++) y[i] -= S[i][j] * x[j];
        x[i] = y[i] / S[i][i];
    }
    for(int i = 0; i < N; i++) 
      delete[] S[i];
    delete[] S;
    delete[] D;
    delete[] y;
}



/**
 * Метод Якоби или Зейделя
 */
void nikulovia::lab5()
{
bool ex = false;
double x1 = 0;
  
  
for (int i = 0; i < N; i++) 
    x[i] = 0;
while (!ex) 
{
    ex = true;
    for (int i = 0; i < N; i++) 
    {
        x1 = b[i];
        for (int j = 0; j < N; j++) 
        {
            if (i != j) 
                x1 -= A[i][j] * x[j];
        }
        x1/= A[i][i];
        if (fabs(x1 - x[i]) > 1E-9) 
          ex = false;
        x[i] = x1;
    }
 }
}



/**
 * Метод минимальных невязок
 */
void nikulovia::lab6()
{
    double *r = new double[N];
    double *ar= new double[N];
    double t=0;
    double ar2=0;
    bool temp = true;
    double t=0;
    double ar2=0;

    while(temp)
    {
        temp=false;
        for (int i=0; i<N; i++)
        {
            r[i]=b[i];
             for (int j=0; j<N; j++)
             {
                 r[i]=r[i]-A[i][j]*x[j];

             }
        }
        for (int i=0; i<N; i++)
        {
            ar[i]=0;
            for (int j=0; j<N; j++)
            {
                ar[i]=ar[i]+A[i][j]*r[j];

            }
        }
        t=0;
        ar2=0;

        for (int i=0; i<N; i++)
        {
            t=t+ar[i]*r[i];
            ar2=ar2+ar[i]*ar[i];
        }

        t= t/ar2;

        for (int i=0; i<N; i++)
        {
            double temp_x=x[i];
            x[i]=x[i]+t*r[i];
            if (fabs(x[i]-temp_x)>1.e-9){ temp=true;
                                        }
        }
    }
    delete[] r;
    delete[] ar;
}



/**
 * Метод сопряженных градиентов
 */
void nikulovia::lab7()
{

}


void nikulovia::lab8()
{

}


void nikulovia::lab9()
{
    double e = 1e-3;
    double *y = new double[N];
    double *yp = new double[N];
    double d = 1e9;
    double lmax = 0;
    double l = 0;

  
    for (int i = 0; i < N; i++) 
    {
        yp[i] = 1;
    }

    while (d > e) 
    {
        for (int i = 0; i < N; i++) 
        {
            y[i] = 0;
            for (int j = 0; j < N; j++) 
                y[i] += A[i][j] * yp[j];
        }

        l = 0;
        for (int i = 0; i < N; i++)
            if (fabs(y[i]) > e && fabs(yp[i]) > e) 
            {
                l = y[i] / yp[i];
                break;
            }

        d = fabs(l - lmax);
        lmax = l;

        for (int i = 0; i < N; i++)
            yp[i] = y[i];
    }

    cout << "lmax  = " << lmax << endl;

    delete[] y;
    delete[] yp;
}


std::string nikulovia::get_name()
{
  return "Nikulov I.A.";
}
