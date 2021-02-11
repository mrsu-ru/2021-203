#include "akishevdv.h"

/**
 * Введение в дисциплину
 */
void akishevdv::lab1()
{
    cout << "Hello world!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void akishevdv::lab2()
{
    int max;
    double sum = 0;

    //прямой ход
    for (int i = 0; i < N; i++)
    {
        max = i;
        double* help_one;
        double help_two;

        for (int j = i + 1; j < N; j++)
        {
            if (fabs(A[j][i]) > fabs(A[max][i]))
            {
                max = j;
            }
        }
        if (max != i)
        {
            help_one = A[i];
            A[i] = A[max];
            A[max] = help_one;

            help_two = b[i];
            b[i] = b[max];
            b[max] = help_two;
        }

        for (int j = N - 1; j > i; j--)
        {
            A[i][j] /= A[i][i];
        }
        b[i] /= A[i][i];
        A[i][i] = 1;

        for (int j = i + 1; j < N; j++)
        {
            for (int k = N - 1; k > i; k--)
            {
                A[j][k] = A[j][k] - A[j][i] * A[i][k];
            }
            b[j] = b[j] - A[j][i] * b[i];
            A[j][i] = 0;
        }
        delete[]help_one;
    }

    //обратный ход
    x[N - 1] = b[N - 1];
    for (int i = N - 2; i > -1; i--)
    {
        for (int j = i + 1; j < N; j++)
        {
            sum += x[j] * A[i][j];
        }
        x[i] = b[i] - sum;
        sum = 0;
    }

}


/**
 * Метод прогонки
 */
void akishevdv::lab3()
{

}

/**
 * Метод Холецкого
 */
void akishevdv::lab4()
{

}


/**
 * Метод Якоби или Зейделя
 */
void akishevdv::lab5()
{

}



/**
 * Метод минимальных невязок
 */
void akishevdv::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void akishevdv::lab7()
{

}


void akishevdv::lab8()
{

}


void akishevdv::lab9()
{

}


std::string akishevdv::get_name()
{
  return "Akishev D.V.";
}
