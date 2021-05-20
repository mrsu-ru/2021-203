#include "inshakovaas.h"

/**
 * Введение в дисциплину
 */
void inshakovaas::lab1()
{
    cout<<"Hello world!";
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void inshakovaas::lab2() {
    int n = N;

    for(int i = 0; i < n; i++)
    {
        int maxi = i;

        for(int j = i + 1; j < n; j++)
        {
            if(A[j][i] > A[maxi][i])
                maxi = j;
        }

        for(int k = 0; k < n; k++)
        {
            swap(A[maxi][k],A[i][k]);
        }

        swap(b[maxi],b[i]);
        double firstElem = A[i][i];

        for(int j = i; j < n; j++)
        {
            A[i][j] /= firstElem;
        }
        b[i] /= firstElem;

        for(int j = i + 1; j < n; j++)
        {
            firstElem = A[j][i];
            for(int k = i; k < n; k++)
            {
                A[j][k] -= A[i][k] * firstElem;
            }
            b[j] -= b[i] * firstElem;
        }
    }

    for (int i = n; i >= 0; i--)
    {
        for(int j = i + 1; j < n; j++)
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
void inshakovaas::lab3()
{
    double* alpha = new double[N];
    double* beta = new double[N];

    alpha[0] = -A[0][1] / A[0][0];
    beta[0] = b[0] / A[0][0];

    for(int i = 1; i < N; i++){
        alpha[i] = -A[i][i + 1] / (A[i][i] + A[i][i - 1] * alpha[i - 1]);
        beta[i] = (b[i] - A[i][i - 1] * beta[i - 1]) / (A[i][i] + A[i][i - 1] * alpha[i - 1]);
    }
    x[N - 1] = beta[N - 1];

    for(int i = N - 2; i >= 0; i--){
        x[i] = alpha[i] * x[i + 1] + beta[i];
    }
}



/**
 * Метод Холецкого
 */
void inshakovaas::lab4()
{

}



/**
 * Метод Якоби или Зейделя
 */
void inshakovaas::lab5()
{
    double eps = 1e-9;
    for(int i = 0; i < N; i++){
        x[i] = b[i];
    }
    bool ex = false;
    while(!ex){
        ex = true;
        for(int i = 0; i < N; i++){
            double temp = b[i];
            for(int j = 0; j < N; j++){
                if(i == j)
                    continue;
                temp -= A[i][j] * x[j];
            }
            temp /= A[i][i];
            if(abs(x[i] - temp) > eps)
                ex = false;
            x[i] = temp;
        }
    }
}



/**
 * Метод минимальных невязок
 */
void inshakovaas::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void inshakovaas::lab7()
{

}


void inshakovaas::lab8()
{

}


void inshakovaas::lab9()
{

}


std::string inshakovaas::get_name()
{
  return "Inshakova A.S.";
}
