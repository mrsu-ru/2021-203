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

}



/**
 * Метод сопряженных градиентов
 */
void chernovaaa::lab7()
{

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
