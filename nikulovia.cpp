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
    double eps = 1e-9;
    double *r = new double[N];
    double *Ar = new double[N];
    bool exit = false;
    for (int i = 0; i < N; i++) x[i] = 0;
    while(!exit){
        exit = true;
        for(int i = 0; i < N; i++){
            r[i] = b[i];
            for(int j = 0; j < N; j++){
                r[i] -= A[i][j] * x[j];
            }
        }
        for(int i = 0; i < N; i++){
            Ar[i] = 0;
            for(int j = 0; j < N; j++){
                Ar[i] += A[i][j] * r[j];
            }
        }
        double rr = 0;
        for(int i = 0; i < N; i++){
            rr += r[i] * r[i];
        }
        double Arr = 0;
        for(int i = 0; i < N; i++){
            Arr += Ar[i] * r[i];
        }
        double t = rr / Arr;
        for(int i = 0; i < N; i++) {
            double tmpx = x[i];
            x[i] += t * r[i];
            if(abs(tmpx - x[i]) > eps){
                exit = false;
            }
        }
    }
}



/**
 * Метод сопряженных градиентов
 */
void nikulovia::lab7()
{

}


void nikulovia::lab8()
{
    double eps = 1e-9;
    double t = 1;
    double** B = new double* [N];
    for(int i = 0; i < N; i++)
        B[i] = new double[N];
    while(t > eps){
        int ii = 1, jj = 0;
        for(int i = 0; i < N; i++)
            for(int j = 0; j < i; j++)
                if(abs(A[i][j]) > abs(A[ii][jj])){
                    ii = i;
                    jj = j;
                }
        double phi = 0.5 * atan(2 * A[ii][jj] / (A[ii][ii] - A[jj][jj]));
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                B[i][j] = A[i][j];
        for(int i = 0; i < N; i++){
            B[i][ii] = A[i][ii] * cos(phi) + A[i][jj] * sin(phi);
            B[i][jj] = A[i][jj] * cos(phi) - A[i][ii] * sin(phi);
        }
        for(int i = 0; i < N; i++){
            A[i][ii] = B[i][ii];
            A[i][jj] = B[i][jj];
        }
        for(int i = 0; i < N; i++){
            A[ii][i] = B[ii][i] * cos(phi) + B[jj][i] * sin(phi);
            A[jj][i] = B[jj][i] * cos(phi) - B[ii][i] * sin(phi);
        }
        t = 0;
        for(int i = 0; i < N; i++)
            for(int j = 0; j < i; j++) {
                t += A[i][j] * A[i][j];
            }
        t *= 2;
    }
    for(int i = 0; i < N; i++)
        x[i] = A[i][i];
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
