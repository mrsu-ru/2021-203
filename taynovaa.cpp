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
            double c = A[i][j] / A[i][i];
            for (int k = i; k < N; k++) {
                A[j][k] -= c * A[i][k];
            }
            b[j] -= c * b[i];
        }
    }
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
