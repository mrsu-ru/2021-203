#include "chernovaaa.h"

/**
 * Введение в дисциплину
 */
void chernovaaa::lab1()
{
    cout << "Hello World!";
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void chernovaaa::lab2()
{
    for(int i = 0; i < N; i++)
    {
        int m = i;
        for (int j = i+1; j < N; j++)
        {
            if (abs(A[j][i]) > abs(A[m][i]))
            {
                m = j;
            }
        }
        swap(A[i], A[m]);
        swap(b[i], b[m]);
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            double c = A[j][i]/A[i][i];
            for (int k = i; k < N; k++)
            {
                A[j][k] -= c * A[i][k];
            }
            b[j] -= c * b[i];
        }
    }
    for (int i = 0; i < N; i++)
    {
        double q = A[i][i];
        for (int j = 0; j < N; j++)
        {
            A[i][j] = A[i][j] / q;
        }
        b[i] /= q;
    }
    x[N - 1] = b[N - 1];
    for(int i = N - 2; i >= 0; i--)
    {
        x[i] = b[i];
        for(int j = i + 1; j < N; j++){
            x[i] -= A[i][j] * x[j];
        }
    }
}



/**
 * Метод прогонки
 */
void chernovaaa::lab3()
{
    double *al = new double[N];
    double *bet = new double[N];
    al[0] = -A[0][1] / A[0][0];
    bet[0] = b[0] / A[0][0];
    for (int i = 1; i <= N - 1; i++)
    {
        al[i] = -A[i][i + 1] / (A[i][i - 1] * al[i - 1] + A[i][i]);
        bet[i] = (b[i] - A[i][i - 1] * bet[i - 1]) / (A[i][i - 1] * al[i - 1] + A[i][i]);
    }
    x[N - 1] = bet[N - 1];
    for (int i = N - 2; i >= 0; i--)
    {
        x[i] = bet[i] + al[i] * x[i + 1];
    }
}



/**
 * Метод Холецкого
 */
void chernovaaa::lab4()
{

}



/**
 * Метод Якоби или Зейделя
 */
void chernovaaa::lab5()
{
    double eps = 1e-9;
    double* xx = new double[N];
    double dif = 1;
    while (dif > eps)
    {
        for (int i = 0; i < N; i++)
            xx[i] = x[i];
        for (int i = 0; i < N; i++)
        {
            double sum = 0;
            for (int j = 0; j < i; j++){
                sum += A[i][j] * x[j];
            }
            for (int j = i + 1; j < N; j++){
                sum += A[i][j] * xx[j];
            }
            x[i] = (b[i] - sum) / A[i][i];
        }
        dif = abs(x[0] - xx[0]);
        for (int i = 1; i < N; i++)
        {
            if (abs(x[i] - xx[i]) > dif)
                dif = abs(x[i] - xx[i]);
        }
    }
    delete[] xx;
}



/**
 * Метод минимальных невязок
 */
void chernovaaa::lab6()
{
    double* f = new double[N];
    double* r = new double[N];
    double* ar = new double[N];
    double* y = new double[N];
    double ak, dif = 1, t, sk1, sk2;

    while((sqrt(dif) > 1e-19))
    {
        for (int i = 0; i < N; i++)
        {
            t = 0;
            for (int j = 0; j < N; j++) {
                t += A[i][j] * x[j];
            }
            r[i] = t - b[i];
            f[i] = 2 * r[i];
        }

        for (int i = 0; i < N; i++)
        {
            t = 0;
            for (int j = 0; j < N; j++) {
                t += A[i][j] * r[j];
            }
            ar[i] = t;
        }

        sk1 = 0;
        sk2 = 0;
        for (int i = 0; i < N; i++) {
            sk1 += abs(ar[i] * r[i]);
            sk2 += abs(ar[i] * ar[i]);
        }
        ak = sk1 / (2 * sk2);

        for (int i = 0; i < N; i++) {
            y[i] = x[i];
        }
        for (int i = 0; i < N; i++) {
            x[i] = x[i] - ak * f[i];
        }

        dif = 0;
        for (int i = 0; i < N; i++) {
            dif += (y[i] - x[i]) * (y[i] - x[i]);
        }
    }
}



/**
 * Метод сопряженных градиентов
 */
void chernovaaa::lab7()
{
    double* r = new double[N];
    double* z = new double[N];
    double* Ar = new double[N];
    double* rp = new double[N];

    double d;
    for(int i = 0; i < N; i++)
        d += b[i] * b[i];

    for (int i = 0; i < N; i++){
        double t = 0;
        for(int j = 0; j < N; j++){
            t += A[i][j] * x[j];
        }
        r[i] = b[i] - t;
        z[i] = r[i];
    }
    double alf, bet, tr = 100;
    while((sqrt(tr / d) > 1e-21)){
        for (int i = 0; i < N; i++){
            double t = 0;
            for(int j = 0; j < N; j++){
                t += A[i][j] * z[j];
            }
            Ar[i] = t;
        }

        double t1 = 0, t2 = 0;
        for (int i = 0; i < N; i++){
            t1 += r[i] * r[i];
            t2 += Ar[i] * z[i];
        }
        alf = t1/t2;

        for(int i=0; i < N; i++){
            rp[i] = r[i];
        }

        for(int i = 0; i < N; i++){
            x[i] = x[i] + alf * z[i];
            r[i] = r[i] - alf * Ar[i];
        }

        for (int i = 0; i < N; i++){
            t1 += r[i] * r[i];
            t2 += rp[i] * rp[i];
        }
        bet = t1/t2;

        for(int i = 0; i < N; i++){
            z[i] = r[i] + bet * z[i];
        }
        tr = 0;
        for(int i = 0; i < N; i++){
            tr += r[i] * r[i];
        }
    }

    delete[] r;
    delete[] rp;
    delete[] Ar;
    delete[] z;
}


void chernovaaa::lab8()
{

}


void chernovaaa::lab9()
{

}


std::string chernovaaa::get_name()
{
  return "Chernova A.A.";
}
