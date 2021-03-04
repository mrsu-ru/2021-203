#include "shabanovdo.h"

/**
 * Введение в дисциплину
 */
void shabanovdo::lab1()
{
  cout << "hello World!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void shabanovdo::lab2()
{
#define forn(i, n) for(int i=0; i<n; i++) //Максим молодец)))
#define foran(i,a, n) for(int i=a; i<n; i++)


#include "shabanovdo.h"

    /**
     * Метод Гаусса с выбором главного элемента
     */

        int n = N;

        for (int i = 0; i < n; i++)
        {
            int maxi = i;
            for (int j = i + 1; j < n; j++)
            {
                if (A[j][i] > A[maxi][i]) maxi = j;
            }
            for (int k = 0; k < n; k++)
            {
                swap(A[maxi][k], A[i][k]);
            }
            swap(b[maxi], b[i]);

            double first = A[i][i];
            for (int j = i; j < n; j++)
            {
                A[i][j] /= first;
            }
            b[i] /= first;
            for (int j = i + 1; j < n; j++)
            {
                first = A[j][i];

                for (int k = i; k < n; k++)

                {
                    A[j][k] -= A[i][k] * first;
                }
                b[j] -= b[i] * first;
            }
        }


        for (int i = n; i >= 0; i--)
        {
            for (int j = i + 1; j < n; j++)
            {
                b[i] += -A[i][j] * x[j];
                A[i][j] = 0;
            }
            x[i] = b[i];
        }

    }

}



/**
 * Метод прогонки
 */
void shabanovdo::lab3()
{

}



/**
 * Метод Холецкого
 */
void shabanovdo::lab4()
{

}



/**
 * Метод Якоби или Зейделя
 */
void shabanovdo::lab5()
{

}



/**
 * Метод минимальных невязок
 */
void shabanovdo::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void shabanovdo::lab7()
{

}


void shabanovdo::lab8()
{

}


void shabanovdo::lab9()
{

}


std::string shabanovdo::get_name()
{
  return "Shabanov D.O.";
}
