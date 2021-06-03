#include "ruzaevaas.h"

/**
 * Введение в дисциплину
 */
void ruzaevaas::lab1()
{
  cout << "hello world!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void ruzaevaas::lab2()
{
double** arr_help = new double*[N];
    for (int i = 0; i < N; i++)
        arr_help[i] = new double[N + 1];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            arr_help[i][j] = A[i][j];
    }

    for (int i = 0; i < N; i++)
        arr_help[i][N] = b[i];

    for (int i = 0; i < N; i++) {
        int max = i;
        for (int j = i + 1; j < N; j++) {
            if (abs(arr_help[j][i]) > abs(arr_help[max][i]))
                max = j;
        }
        if (max != i) {
            for (int k = 0; k < N + 1; k++)
                swap(arr_help[i][k], arr_help[max][k]);
        }

        double helpel = arr_help[i][i];
        for (int j = i; j < N + 1; j++)
            arr_help[i][j] /= helpel;

        for (int j = i + 1; j < N; j++) {
            helpel = arr_help[j][i];
            arr_help[j][i] = 0;
            for (int k = i + 1; k < N + 1; k++)
                arr_help[j][k] -= arr_help[i][k] * helpel;
        }
    }
    int n = N + 1;
    for (int i = N - 1; i > 0; i--) {
        double h = 0;
        for (int j = i + 1; j < n; j++) {
            double help_el = arr_help[i - 1][j - 1];
            arr_help[i - 1][j - 1] = 0;
            h += arr_help[j - 1][n - 1] * help_el;
        }
        arr_help[i - 1][n - 1] = arr_help[i - 1][n - 1] - h;
    }

    for (int i = 0; i < N; i++)
        x[i] = arr_help[i][N];

}



/**
 * Метод прогонки
 */
void ruzaevaas::lab3()
{

}



/**
 * Метод Холецкого
 */
void ruzaevaas::lab4()
{

}



/**
 * Метод Якоби или Зейделя
 */
void ruzaevaas::lab5()
{

}



/**
 * Метод минимальных невязок
 */
void ruzaevaas::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void ruzaevaas::lab7()
{

}


void ruzaevaas::lab8()
{

}


void ruzaevaas::lab9()
{

}


std::string ruzaevaas::get_name()
{
  return "Ruzaeva A.S.";
}
