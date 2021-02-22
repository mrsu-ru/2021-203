﻿#include "utkinnv.h"

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
    double *al = new double[N];
    double *bt = new double[N];
    al[0] = -A[0][1]/A[0][0]; bt[0]=b[0]/A[0][0];
    for(int i = 1; i < N; i++){
        double temp = A[i][i - 1] * al[i-1]+A[i][i];
        al[i] = -A[i][i + 1]/temp;
        bt[i] = (b[i] - A[i][i - 1] * bt[i - 1])/temp;
    }
    x[N-1] = bt[N - 1];
    for(int i = N - 2; i>-1; i--){
        x[i]=al[i]*x[i+1] + bt[i];
    }
    delete[] al;
    delete[] bt;
}


/**
 * Метод Холецкого
 */
void utkinnv::lab4() {

}


/**
 * Метод Якоби или Зейделя
 */
void utkinnv::lab5() {

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
