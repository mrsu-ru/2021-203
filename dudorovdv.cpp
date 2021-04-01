#include "dudorovdv.h"

/**
 * Введение в дисциплину
 */
void dudorovdv::lab1()
{
    cout << "hello world!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void dudorovdv::lab2()
{
    int i=0;
    int j=0;
 //   double c;
    double d;
    int k;
    for (i = 0; i < N; i++) {
        int max = 0;
        for (j = 0; j < N; j++){
            if (abs(A[max][i])<abs(A[j][i])) max = j;
        }
        swap(A[i], A[max]);
        swap(b[i],b[max]);
        for (j = i + 1; j < N; j++) {
            double c = A[j][i] / A[i][i];
            for (k = i + 1; k < N; k++){
                A[j][k] -= c * A[i][k];
            }
            b[j] -= c * b[i];
            A[j][i] = 0;
        }
    }
    for(i = 0; i < N; i++){
        d = A[i][i];
        for(j = 0; j < N; j++){
            A[i][j]/= d;
        }
        b[i]/=d;
    }
    for (i = N - 1; i >= 0; i--) {
        x[i] = b[i];
        for (j = i + 1; j < N; j++) x[i] -= A[i][j] * x[j];
    }
}




/**
 * Метод прогонки
 */
void dudorovdv::lab3()
{

}



/**
 * Метод Холецкого
 */
void dudorovdv::lab4()
{

}



/**
 * Метод Якоби или Зейделя
 */
void dudorovdv::lab5()
{

}



/**
 * Метод минимальных невязок
 */
void dudorovdv::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void dudorovdv::lab7()
{

}


void dudorovdv::lab8()
{

}


void dudorovdv::lab9()
{

}


std::string dudorovdv::get_name()
{
  return "Dudorov D.V.";
}
