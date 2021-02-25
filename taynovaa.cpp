#include "taynovaa.h"

/**
 * Введение в дисциплину
 */
void taynovaa::lab1() {
    cout << "hello world!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void taynovaa::lab2() {
    for (int i = 0; i < N; i++) {
        int index_max = i;

        for (int m = i; m < N; m++) {
            if (fabs(A[index_max][i]) < fabs(A[m][i]))
                index_max = m;
        }

        swap(A[index_max], A[i]);
        swap(b[index_max], b[i]);

        for (int j = i + 1; j < N; j++) {
            double c = A[j][i] / A[i][i];
            for (int k = i; k < N; k++) {
                A[j][k] -= c * A[i][k];
            }
            b[j] -= c * b[i];
        }
    }
    // обратный
    for (int i = N - 1; i >= 0; i--) {
        double c = 0;
        for (int j = i + 1; j < N; j++) {
            c += A[i][j] * x[j];
        }
        x[i] = (b[i] - c) / A[i][i];
    }
}


/**
 * Метод прогонки
 */
void taynovaa::lab3() {
    double *alpha = new double[N];
    double *betta = new double[N];

    double y = A[0][0];
    alpha[0] = -A[0][1] / y;
    betta[0] = b[0] / y;

    for (int i = 1; i < N - 1; i++) {
        y = A[i][i] + A[i][i - 1] * alpha[i - 1];
        alpha[i] = -A[i][i + 1] / y;
        betta[i] = (b[i] - A[i][i - 1] * betta[i - 1]) / y;
    }

    y = A[N - 1][N - 1] + A[N - 1][N - 2] * alpha[N - 2];
    betta[N - 1] = (b[N - 1] - A[N - 1][N - 2] * betta[N - 2]) / y;

    x[N - 1] = betta[N - 1];

    for (int i = N - 2; i >= 0; i--) {
        x[i] = alpha[i] * x[i + 1] + betta[i];
    }

}


/**
 * Метод Холецкого
 */
void taynovaa::lab4() {

}


/**
 * Метод Якоби или Зейделя
 */
void taynovaa::lab5() {

}


/**
 * Метод минимальных невязок
 */
void taynovaa::lab6() {

}


/**
 * Метод сопряженных градиентов
 */
void taynovaa::lab7() {

}


void taynovaa::lab8() {

}


void taynovaa::lab9() {

}


std::string taynovaa::get_name() {
    return "Taynov A. A.";
}
