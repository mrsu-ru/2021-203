#include "utkinnv.h"

/**
 * Введение в дисциплину
 */
void utkinnv::lab1() {
    cout << "Hello world! Check" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void utkinnv::lab2() {
    for (int i = 0; i < N; i++) {
        int maxj = 0;
        for (int j = 0; j < N; j++) if (abs(A[j][i]) > abs(A[maxj][i])) maxj = j;
        swap(A[i], A[maxj]);
        swap(b[i], b[maxj]);
        for (int j = i + 1; j < N; j++) {
            double c = A[j][i] / A[i][i];
            for (int k = i + 1; k < N; k++) A[j][k] -= c * A[i][k];
            b[j] -= c * b[i];
            A[j][i] = 0;
        }
    }
    for (int i = N - 1; i > -1; i--) {
        x[i] = b[i] / A[i][i];
        for (int j = i + 1; j < N; j++) x[i] -= A[i][j] / A[i][i] * x[j];
        A[i][i] = 1;
    }
}


/**
 * Метод прогонки
 */
void utkinnv::lab3() {
    auto al = new double[N];
    auto bt = new double[N];
    al[0] = -A[0][1] / A[0][0];
    bt[0] = b[0] / A[0][0];
    for (int i = 1; i < N; i++) {
        double temp = A[i][i - 1] * al[i - 1] + A[i][i];
        al[i] = -A[i][i + 1] / temp;
        bt[i] = (b[i] - A[i][i - 1] * bt[i - 1]) / temp;
    }
    x[N - 1] = bt[N - 1];
    for (int i = N - 2; i > -1; i--) x[i] = al[i] * x[i + 1] + bt[i];
    delete[] al;
    delete[] bt;
}


/**
 * Метод Холецкого
 */
void utkinnv::lab4() {
    auto **s = new double *[N];
    auto *d = new double[N];
    for (int i = 0; i < N; ++i) {
        s[i] = new double[N];
    }
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < i; k++) A[i][i] -= s[k][i] * d[k] * s[k][i];
        d[i] = A[i][i] < 0 ? -1 : 1;
        s[i][i] = sqrt(d[i] * A[i][i]);
        for (int j = i + 1; j < N; j++) {
            for (int k = 0; k < j; k++) A[i][j] -= s[k][i] * d[k] * s[k][j];
            s[i][j] = A[i][j] / (s[i][i] * d[i]);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) b[i] -= s[j][i] * d[j] * b[j];
        b[i] /= s[i][i] * d[i];
    }
    for (int i = N - 1; i > -1; i--) {
        for (int k = i + 1; k < N; k++) b[i] -= s[i][k] * x[k];
        x[i] = b[i] / s[i][i];
    }

    for (int i = 0; i < N; i++) {
        delete[] s[i];
    }
    delete[] s;
    delete[] d;
}


/**
 * Метод Якоби или Зейделя
 */
void utkinnv::lab5() {
    //Метод Зейделя
    for (int i = 0; i < N; i++) x[i] = 1;
    double *X = new double[N];
    bool isContinue = true;
    while (isContinue) {
        isContinue = false;
        for (int i = 0; i < N; i++) {
            X[i] = b[i];
            for (int j = 0; j < i; j++) X[i] -= A[i][j] * X[j];
            for (int j = i + 1; j < N; j++) X[i] -= A[i][j] * x[j];
            X[i] /= A[i][i];
            if (fabs(X[i] - x[i]) > 1e-9) isContinue = true;
            x[i] = X[i];
        }
    }
    delete[] X;
}


/**
 * Метод минимальных невязок
 */
void utkinnv::lab6() {

}


/**
 * Метод сопряженных градиентов
 */
void utkinnv::lab7() {

}


void utkinnv::lab8() {

}


void utkinnv::lab9() {

}


std::string utkinnv::get_name() {
    return "Utkin N.V.";
}
