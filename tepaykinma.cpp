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

}



/**
 * Метод Холецкого
 */
void tepaykinma::lab4()
{

}



/**
 * Метод Якоби или Зейделя
 */
void tepaykinma::lab5()
{

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

