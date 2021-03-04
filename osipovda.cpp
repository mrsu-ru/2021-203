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
    double *alpha = new double[N];
    double *beta = new double[N];

    alpha[0] = A[0][1] / A[0][0];
    beta[0] = b[0] / A[0][0];
    for (int i = 1; i < N; i++) {
        alpha[i] = A[i][i + 1] / (A[i][i] - A[i][i - 1] * alpha[i - 1]);
        beta[i] = (b[i] - A[i][i - 1] * beta[i - 1]) / (A[i][i] - A[i][i - 1] * alpha[i - 1]);
    }

    x[N - 1] = beta[N - 1];
    for (int i = N - 2; i >= 0; i--) {
        x[i] = beta[i] - alpha[i] * x[i + 1];
    }

    delete[]alpha;
    delete[]beta;
}


/**
 * Метод Холецкого
 */
void osipovda::lab4() {
    double **S = new double *[N];
    for (int i = 0; i < N; i++) {
        S[i] = new double[N];
    }
    double *D = new double[N];

    //find S - up triangle
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < i; k++) {
            A[i][i] -= S[k][i] * D[k] * S[k][i];
        }
        D[i] = A[i][i] >= 0 ? 1 : -1;
        S[i][i] = sqrt(D[i] * A[i][i]);
        for (int j = i + 1; j < N; j++) {
            for (int k = 0; k < j; k++) {
                A[i][j] -= S[k][i] * D[k] * S[k][j];
            }
            S[i][j] = A[i][j] / (S[i][i] * D[i]);
        }
    }

    //StDSx=b, StDy = b, find y
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) b[i] -= S[j][i] * D[j] * b[j];
        b[i] /= S[i][i] * D[i];
    }

    //Sx = y, find x
    for (int i = N - 1; i >= 0; i--) {
        for (int k = i + 1; k < N; k++) b[i] -= S[i][k] * x[k];
        x[i] = b[i] / S[i][i];
    }

    for (int i = 0; i < N; i++) {
        delete[] S[i];
    }
    delete[] S;
    delete[] D;
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
