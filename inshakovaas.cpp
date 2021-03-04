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
