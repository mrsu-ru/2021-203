#include "velmiskinnm.h"

/**
 * Введение в дисциплину
 */
void velmiskinnm::lab1()
{
  cout << "HELLO, WORLD!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void velmiskinnm::lab2(){
    int rows = N;

    for (int i = 0; i < rows; i++){
        int maxElement = i;
        for (int j = i + 1; j < rows; j++){
            if (A[j][i] > A[maxElement][i])
                maxElement = j;
        }
        for (int k = 0; k < rows; k++){
            swap(A[maxElement][k], A[i][k]);
        }
        swap(b[maxElement], b[i]);


        double first = A[i][i];
        for (int j = i; j < rows; j++){
            A[i][j] /= first;
        }

        b[i] /= first;
        for (int j = i + 1; j < rows; j++){
            first = A[j][i];

            for (int k = i; k < rows; k++){
                A[j][k] -= A[i][k] * first;
            }
            b[j] -= b[i] * first;
        }
    }

    for (int i = rows; i >= 0; i--){
        for (int j = i + 1; j < rows; j++){
            b[i] += -A[i][j] * x[j];
            A[i][j] = 0;
        }
        x[i] = b[i];
    }
}



/**
 * Метод прогонки
 */
void velmiskinnm::lab3()
{

}



/**
 * Метод Холецкого
 */
void velmiskinnm::lab4()
{

}



/**
 * Метод Якоби или Зейделя
 */
void velmiskinnm::lab5()
{

}



/**
 * Метод минимальных невязок
 */
void velmiskinnm::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void velmiskinnm::lab7()
{

}


void velmiskinnm::lab8()
{

}


void velmiskinnm::lab9()
{

}


std::string velmiskinnm::get_name()
{
  return "Velmiskin N.M.";
}
