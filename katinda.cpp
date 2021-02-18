#include "katinda.h"

/**
 * Введение в дисциплину
 */
void katinda::lab1()
{
    cout << "Hello world!";
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void katinda::lab2()
{
    for(int i = 0; i < N; i++){
        int mx = i;
        for(int j = i + 1; j < N; j++){
            if(abs(A[i][j]) > abs(A[i][mx])){
                mx = j;
            }
        }
        swap(A[i], A[mx]);
        swap(b[i], b[mx]);
        for(int j = i + 1; j < N; j++){
            double c = A[j][i]/A[i][i];
            for(int k = i; k < N; k++){
                A[j][k] -= c*A[i][k];
            }
            b[j] -= c*b[i];
        }
    }
    for(int i = 0; i < N; i++){
        double c = A[i][i];
        for(int j = i; j < N; j++){
            A[i][j] /= c;
        }
        b[i] /= c;
    }
    x[N - 1] = b[N - 1];
    for(int i = N - 2; i >= 0; i--){
        x[i] = b[i];
        for(int j = i + 1; j < N; j++){
            x[i] -= A[i][j]*x[j];
        }
    }
}



/**
 * Метод прогонки
 */
void katinda::lab3()
{

}



/**
 * Метод Холецкого
 */
void katinda::lab4()
{

}



/**
 * Метод Якоби или Зейделя
 */
void katinda::lab5()
{

}



/**
 * Метод минимальных невязок
 */
void katinda::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void katinda::lab7()
{

}


void katinda::lab8()
{

}


void katinda::lab9()
{

}


std::string katinda::get_name()
{
  return "Katin D.A.";
}
