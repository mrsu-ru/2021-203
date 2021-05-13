#define forn(i, n) for(int i=0; i<n; i++)
#define foran(i,a, n) for(int i=a; i<n; i++)

#include "tepaykinma.h"

/**
 * Введение в дисциплину
 */
void tepaykinma::lab1()
{
    cout << "Hello World!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void tepaykinma::lab2() {
    int n = N;

    forn(i, n)
    {
        //sort(matr.begin() + i, matr.end(), comp_first);

        int maxi = i;
        foran(j, i + 1, n)
        {
            if(A[j][i] > A[maxi][i]) maxi = j;
        }
        forn(k,n)
        {
            swap(A[maxi][k],A[i][k]);
        }
        swap(b[maxi],b[i]);

        double first = A[i][i];
        foran(j, i, n)
        {
            A[i][j] /= first;
        }
        b[i] /= first;
        foran(j, i + 1, n)
        {
            first = A[j][i];
            foran(k, i, n)
            {
                A[j][k] -= A[i][k] * first;
            }
            b[j] -= b[i] * first;
        }
    }


    for (int i = n; i >= 0; i--)
    {
        foran(j, i + 1, n)
        {
            b[i] += -A[i][j] * x[j];
            A[i][j] = 0;
        }
        x[i] = b[i];
    }

}



/**
 * Метод прогонки
 */
void tepaykinma::lab3()
{
    double* y = new double[N];
    double* alpha = new double[N];
    double* beta = new double[N];

    //  c = A[i][i+1]  i = 0,...,N-2
    //  a = A[i][i-1]  i = 0,...,N-1

    y[0] = A[0][0];
    alpha[0] = -A[0][0+1] / y[0];
    beta[0] = b[0] / y[0];
    foran(i, 1, N - 1)
    {
        y[i] = A[i][i] + A[i][i-1]*alpha[i-1];
        alpha[i] = -A[i][i+1] / y[i];
        beta[i] = (b[i] - A[i][i-1]*beta[i-1]) / y[i];
    }
    y[N - 1] = A[N - 1][N - 1] + A[N - 1][N - 2] * alpha[N - 2];
    beta[N - 1] = (b[N - 1] - A[N - 1][N - 2] * beta[N - 2]) / y[N - 1];

    x[N - 1] = beta[N - 1];
    for(int i = N - 2; i >= 0; i--)
    {
        x[i] = alpha[i]*x[i+1] + beta[i];

    }





    delete[] y;
    delete[] alpha;
    delete[] beta;
}



/**
 * Метод Холецкого
 */
void tepaykinma::lab4()
{
    int n = N;
    double** l = new double*[n];

    forn(i, n)
    {
        l[i] = new double[n];
    }

    l[0][0] = sqrt(A[0][0]);
    foran(i, 1, n)
    {
        l[i][0] = A[i][0]/l[0][0];
    }

    foran(i, 1, n)
    {
        double sum = 0;
        forn(p, i-1)
        {
            sum+=l[i][p] * l[i][p];
        }

        l[i][i] = sqrt(A[i][i] - sum);
    }

    foran(i, 1, n-1)
    {
        foran(j, i+1, n)
        {
            double sum = 0;
            forn(p, i-1)
            {
                sum+=l[i][p] * l[j][p];
            }
            l[j][i] = (A[j][i] - sum) / l[i][i];
        }
    }

    double* y = new double[n];


    for (int i = 0; i < n; i++)
    {
        foran(j, i + 1, n)
        {
            b[i] += -l[i][j] * x[j];
            l[i][j] = 0;
        }
        y[i] = b[i] / l[i][i];
    }



    for (int i = n-1; i >= 0; i--)
    {
        foran(j, i + 1, n)

        {
            y[i] += -l[i][j] * x[j];
            l[i][j] = 0;
        }
        x[i] = y[i] / l[i][i];
    }






}



/**
 * Метод Якоби или Зейделя
 */
void tepaykinma::lab5()
{
    int n = N;
    double eps = 1e-20;
    auto* x1 = new double[N];
    forn(i,n)
    {
        x1[i] = 0;
    }
    double norm = 0;
    do{
        forn(i, n) {
            double sum = 0;
            forn(j, n) {

                if (i != j)sum += A[i][j] * x[j];
            }
            x1[i] = (b[i] - sum) / A[i][i];
        }
        norm = 0;
        forn(i,n)
        {
            norm+=fabs(x1[i]-x[i]);
        }

        forn(i,n) x[i] = x1[i];

    }while(norm > eps);






}



/**
 * Метод минимальных невязок
 */
void tepaykinma::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void tepaykinma::lab7()
{

}


void tepaykinma::lab8()
{

}


void tepaykinma::lab9()
{

}


std::string tepaykinma::get_name()
{
    return "Tepaykin M.A.";
}




#undef LL
#undef forn
#undef foran

