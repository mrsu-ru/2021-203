#include "guskovaim.h"

/**
 * Введение в дисциплину
 */
void guskovaim::lab1()
{
	cout << "Hello world!!!";

}


/**
 * Метод Гаусса с выбором главного элемента
 */
void guskovaim::lab2()
{
    for (int i = 0; i < N; i++) {
        int max = 0;
        for (int j = 0; j < N; j++){
            if (abs(A[max][i])<abs(A[j][i])) max = j;
        }
        swap(A[i], A[max]);
        swap(b[i], b[max]);
        for (int j = i + 1; j < N; j++) {
            double c = A[j][i] / A[i][i];
            for (int k = i + 1; k < N; k++){
                A[j][k] -= c * A[i][k];
            }
            b[j] -= c * b[i];
            A[j][i] = 0;
        }
    }
    for(int i = 0; i < N; i++){
        double d = A[i][i];
        for(int j = 0; j < N; j++){
            A[i][j]/= d;
        }
        b[i]/=d;
    }
    for (int i = N - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < N; j++) x[i] -= A[i][j] * x[j];
    }

}



/**
 * Метод прогонки
 */
void guskovaim::lab3()
{

}



/**
 * Метод Холецкого
 */
void guskovaim::lab4()
{

}



/**
 * Метод Якоби или Зейделя
 */
void guskovaim::lab5()
{

}



/**
 * Метод минимальных невязок
 */
void guskovaim::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void guskovaim::lab7()
{

}


void guskovaim::lab8()
{

}


void guskovaim::lab9()
{

}


std::string guskovaim::get_name()
{
  return "Guskova I.M.";
}
