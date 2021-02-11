#include "osipovda.h"

/**
 * Введение в дисциплину
 */
void osipovda::lab1() {
    cout << "Hello world!!!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void osipovda::lab2() {
    for (int i = 0; i < N; i++) {
        double mx = A[i][i];
        int mxi = i;
        for (int j = i + 1; j < N; j++) {
            if (fabs(A[j][i]) > mx) {
                mx = fabs(A[j][i]);
                mxi = j;
            }
        }
        swap(A[i], A[mxi]);
        swap(b[i], b[mxi]);
        for (int j = i + 1; j < N; j++) {
            double c = A[j][i] / A[i][i];
            for (int k = i + 1; k < N; k++) {
                A[j][k] -= c * A[i][k];
            }
            A[j][i] = 0;
            b[j] -= c * b[i];
        }
    }

    for (int i = 0; i < N; i++) {
        double c = A[i][i];
        for (int j = i + 1; j < N; j++) {
            A[i][j] /= c;
        }
        b[i] /= c;
        A[i][i] = 1;
    }

    for (int i = N - 1; i >= 0; i--) {
        double mx = A[i][i];
        int mxi = i;
        for (int j = i - 1; j >= 0; j--) {
            if (fabs(A[j][i]) > mx) {
                mx = fabs(A[j][i]);
                mxi = j;
            }
        }
        swap(A[i], A[mxi]);
        swap(b[i], b[mxi]);
        for (int j = i - 1; j >= 0; j--) {
            double c = A[j][i];
            A[j][i] = 0;
            b[j] -= c * b[i];
        }
    }

    for (int i = 0; i < N; i++) {
        x[i] = b[i];
    }
}


/**
 * Метод прогонки
 */
void osipovda::lab3() {

}


/**
 * Метод Холецкого
 */
void osipovda::lab4() {

}


/**
 * Метод Якоби или Зейделя
 */
void osipovda::lab5() {

}


/**
 * Метод минимальных невязок
 */
void osipovda::lab6() {

}


/**
 * Метод сопряженных градиентов
 */
void osipovda::lab7() {

}


void osipovda::lab8() {

}


void osipovda::lab9() {

}


std::string osipovda::get_name() {
    return "Osipov D.A.";
}
