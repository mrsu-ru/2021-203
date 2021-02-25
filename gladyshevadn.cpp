#include "gladyshevadn.h"

/**
 * Введение в дисциплину
 */
void gladyshevadn::lab1()
{
	cout << "Hello, world!";
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void gladyshevadn::lab2()
{
    for (int i = 0; i < N; i++){
        int maxi = i;
        for (int j = i + 1; j < N; j++){
            if (abs(A[j][i]) > abs(A[maxi][i])) maxi = j;
        }
        if (maxi != i){
            swap(A[i], A[maxi]);
            swap(b[i], b[maxi]);
        }
        for (int j = i + 1; j < N; j++){
            double coeff = A[j][i] / A[i][i];
            for (int k = i + 1; k < N; k++) A[j][k] -= (coeff * A[i][k]);
            A[j][i] = 0;
            b[j] -= (coeff * b[i]);
        }
    }
    for (int i=N-1; i>=0; i--){
        for (int j=i+1; j<N; j++) b[i] -= (A[i][j] * x[j]);
        x[i] = b[i] / A[i][i];
        A[i][i] = 1;
    }
}



/**
 * Метод прогонки
 */
void gladyshevadn::lab3()
{

}



/**
 * Метод Холецкого
 */
void gladyshevadn::lab4()
{

}



/**
 * Метод Якоби или Зейделя
 */
void gladyshevadn::lab5()
{

}



/**
 * Метод минимальных невязок
 */
void gladyshevadn::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void gladyshevadn::lab7()
{

}


void gladyshevadn::lab8()
{

}


void gladyshevadn::lab9()
{

}


std::string gladyshevadn::get_name()
{
  return "Gladysheva D.N.";
}
