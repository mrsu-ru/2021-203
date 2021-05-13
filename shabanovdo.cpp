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
    int m = N + 1;

    double** arr = new double*[N];
    for (int i = 0; i < N; i++) {
        arr[i] = new double[N + 1];
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = A[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        arr[i][N] = b[i];
    }

//---------прямой ход---------—
    for (int i = 0; i < N; i++) {
        int max = i;
        for (int j = i + 1; j < N; j++) {
            if (abs(arr[j][i]) > abs(arr[max][i]))
                max = j;
        }
        if (max != i) {
            for (int k = 0; k < N + 1; k++) {
                swap(arr[i][k], arr[max][k]);
            }
        }

        double helpel = arr[i][i];
        for (int j = i; j < N + 1; j++) {
            arr[i][j] /= helpel;
        }
        for (int j = i + 1; j < N; j++) {
            helpel = arr[j][i];
            arr[j][i] = 0;
            for (int k = i + 1; k < N + 1; k++)
                arr[j][k] -= arr[i][k] * helpel;
        }
    }

//------------обратный ход---------—
    for (int i = N - 1; i > 0; i--) {
        double h = 0;
        for (int j = i + 1; j < m; j++) {
            double helpel = arr[i - 1][j - 1];
            arr[i - 1][j - 1] = 0;
            h += arr[j - 1][m - 1] * helpel;
        }
        arr[i - 1][m - 1] = arr[i - 1][m - 1] - h;
    }

    for (int i = 0; i < N; i++) {
        x[i] = arr[i][N];
    }
}



/**
 * Метод прогонки
 */
void shabanovdo::lab3()
{
double *alpha = new double[N];
double *betta = new double[N];

alpha[0] = -A[0][1] / A[0][0];
betta[0] = b[0] / A[0][0];

for (int i = 1; i < N - 1; i++) {
alpha[i] = -A[i][i + 1] / (A[i][i - 1] * alpha[i - 1] + A[i][i]);
betta[i] = (-A[i][i - 1] * betta[i - 1] + b[i]) / (A[i][i - 1] * alpha[i - 1] + A[i][i]);
}

betta[N - 1] = (-A[N - 1][N - 2] * betta[N - 2] + b[N - 1]) / (A[N - 1][N - 2] * alpha[N - 2] + A[N - 1][N - 1]);

x[N - 1] = betta[N - 1];

for (int i = N - 2; i >= 0; i--) {
x[i] = betta[i] + alpha[i] * x[i + 1];
} 
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
