#include "svetilnikovdb.h"

/**
 * Введение в дисциплину
 */
void svetilnikovdb::lab1()
{
  cout << "Hello world!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void svetilnikovdb::lab2()
{
    for (int i = 0; i < N; i++) {
        int ma = 0;
        for (int j = 0; j < N; j++){
            if (abs(A[ma][i])<abs(A[j][i])) ma = j;
        }
        swap(A[i], A[ma]);
        swap(b[i], b[ma]);
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
void svetilnikovdb::lab3()
{

}



/**
 * Метод Холецкого
 */
void svetilnikovdb::lab4()
{

}



/**
 * Метод Якоби или Зейделя
 */
void svetilnikovdb::lab5()
{

}



/**
 * Метод минимальных невязок
 */
void svetilnikovdb::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void svetilnikovdb::lab7()
{

}


void svetilnikovdb::lab8()
{

}


void svetilnikovdb::lab9()
{

}


std::string svetilnikovdb::get_name()
{
  return "Svetilnikov D.B.";
}
