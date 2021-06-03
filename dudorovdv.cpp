#include "dudorovdv.h"

/**
 * Введение в дисциплину
 */
void dudorovdv::lab1()
{
    cout << "hello world!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void dudorovdv::lab2()
{
    int i=0;
    int j=0;
 //   double c;
    double d;
    int k;
    for (i = 0; i < N; i++) {
        int max = 0;
        for (j = 0; j < N; j++){
            if (abs(A[max][i])<abs(A[j][i])) max = j;
        }
        swap(A[i], A[max]);
        swap(b[i],b[max]);
        for (j = i + 1; j < N; j++) {
            double c = A[j][i] / A[i][i];
            for (k = i + 1; k < N; k++){
                A[j][k] -= c * A[i][k];
            }
            b[j] -= c * b[i];
            A[j][i] = 0;
        }
    }
    for(i = 0; i < N; i++){
        d = A[i][i];
        for(j = 0; j < N; j++){
            A[i][j]/= d;
        }
        b[i]/=d;
    }
    for (i = N - 1; i >= 0; i--) {
        x[i] = b[i];
        for (j = i + 1; j < N; j++) x[i] -= A[i][j] * x[j];
    }
}




/**
 * Метод прогонки
 */
void dudorovdv::lab3()
{
    bool converge = false;
    for(int i = 0; i < N; i++){
        if(fabs(A[i][i]) < fabs(A[i][i-1]) + fabs(A[i][i+1])) return;
        if(fabs(A[i][i]) > fabs(A[i][i-1]) + fabs(A[i][i+1])) converge = true;
    }
    if(fabs(A[0][1]) > 1 || fabs(A[N-1][N-2]) > 1) return;
    if(fabs(A[0][1]) + fabs(A[N-1][N-2])<2) converge = true;
    if(converge == false) return;

    double alpha[N];
    double beta[N];
    for(int i = 0; i < N; i++){
        if(i == 0) {
            alpha[i] = -A[i][i+1] / A[i][i];
            beta[i] = b[i] / A[i][i];
        }
        else if(i == N - 1){
            beta[i] = (b[i] - A[i][i-1] * beta[i-1]) / (A[i][i] + A[i][i-1] * alpha[i-1]);
        }
        else{
            x[i] = A[i][i] + A[i][i-1] * alpha[i-1];
            alpha[i] = -A[i][i+1] / x[i];
            beta[i] = (b[i] - A[i][i-1] * beta[i - 1]) / x[i];
        }
    }
    for(int i = N-1; i >= 0; i--){
        if(i == N-1) x[i] = beta[i];
        else{
            x[i] = alpha[i] * x[i+1] + beta[i];
        }
    }
}



/**
 * Метод Холецкого
 */
void dudorovdv::lab4()
{

}



/**
 * Метод Якоби или Зейделя
 */
void dudorovdv::lab5()
{
    bool exit = false;
    double ix = 0;
    int i = 0;
    int j = 0;
    for (i = 0; i < N; i++) x[i] = 0;
    while (exit == false) {
        exit = true;
        for (i = 0; i < N; i++) {
            ix = b[i];
            for (j = 0; j < N; j++) {
                if (i != j) {
                    ix -= A[i][j] * x[j];
                }
            }
            ix /= A[i][i];
            if (fabs(ix - x[i]) > 1E-9) exit = false;
            x[i] = ix;
        }
    }
}


/**
 * Метод минимальных невязок
 */
void dudorovdv::lab6()
{
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            if(A[i][j] != A[j][i]) return;
    }
    double *re = new double[N];
    double *Ark = new double[N];
    double t;
    double xk;
    for (int i = 0; i < N; i++) {
        x[i] = 0;
        re[i] = 0;
        Ark[i] = 0;
    }
    bool exit = false;
    while (exit == false) {
        exit = true;
        for (int i = 0; i < N; i++) {
            re[i] = b[i];
            for (int j = 0; j < N; j++) {
                re[i] -= A[i][j] * x[j];
            }
        }
        for (int i = 0; i < N; i++) {
            Ark[i] = 0;
            for (int j = 0; j < N; j++) {
                Ark[i] += A[i][j] * re[j];
            }
        }
        double t1 = 0, t2 = 0;
        for (int i = 0; i < N; i++) {
            t1 += Ark[i] * re[i];
            t2 += Ark[i] * Ark[i];
        }
        t = t1 / t2;
        for (int i = 0; i < N; i++) {
            xk = x[i];
            x[i] += t * re[i];
            if (fabs(x[i] - xk) > 1E-9) exit = false;
        }
    }
}


/**
 * Метод сопряженных градиентов
 */
void dudorovdv::lab7()
{

}


void dudorovdv::lab8()
{

}


void dudorovdv::lab9()
{

}


std::string dudorovdv::get_name()
{
  return "Dudorov D.V.";
}
