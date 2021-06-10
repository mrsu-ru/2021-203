#include "parshindi.h"

/**
 * Введение в дисциплину
 */
void parshindi::lab1()
{
  cout << "hello world!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void parshindi::lab2()
{

}



/**
 * Метод прогонки
 */
void parshindi::lab3()
{

}



/**
 * Метод Холецкого
 */
void parshindi::lab4()
{

}



/**
 * Метод Якоби или Зейделя
 */
void parshindi::lab5()
{
 double e = 1e-9;

    double* predres = new double[N];

    while (1) {
        for (int i = 0; i < N; i++)
            predres[i] = x[i];

        for (int i = 0; i < N; i++) {
            double s = 0;

            for (int j = 0; j < i; j++){
                s += A[i][j] * x[j];
            }

            for (int j = i + 1; j < N; j++){
                s += A[i][j] * predres[j];
            }

            x[i] = (b[i] - s) / A[i][i];
        }

        double d = abs(x[0] - predres[0]);
        for (int i = 1; i < N; i++)
            if (abs(x[i] - predres[i]) > d)
                d = abs(x[i] - predres[i]);

        if (d < e)
            break;
    }

    delete[] predres;
}



/**
 * Метод минимальных невязок
 */
void parshindi::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void parshindi::lab7()
{

}


void parshindi::lab8()
{

}


void parshindi::lab9()
{
 double e = 1e-3;
    double *y = new double[N];
    double *yPred = new double[N];

    for (int i = 0; i < N; i++) {
        yPred[i] = 1;
    }

    double d = 1e9;
    double maxl = 0;

    while (d > e) {
        for (int i = 0; i < N; i++) {
            y[i] = 0;
            for (int j = 0; j < N; j++) {
                y[i] += A[i][j] * yPred[j];
            }
        }

        double l = 0;
        for (int i = 0; i < N; i++) {
            if (fabs(y[i]) > e && fabs(yPred[i]) > e) {
                l = y[i] / yPred[i];
                break;
            }
        }

        d = fabs(l - maxl);
        maxl = l;

        for (int i = 0; i < N; i++) {
            yPred[i] = y[i];
        }
    }

    cout << "Max lambda = " << maxl << endl;

    delete[] y;
    delete[] yPred;
}


std::string parshindi::get_name()
{
  return "Parshin D.I.";
}
