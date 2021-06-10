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

}



/**
 * Метод минимальных невязок
 */
void nikulovia::lab6()
{

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
