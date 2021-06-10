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
  int i=0;
    int j=0;
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
void parshindi::lab3()
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
 double eps = 1e-9;
    double *r = new double[N];
    double *Ar = new double[N];
    bool exit = false;
    for (int i = 0; i < N; i++) x[i] = 0;
    while(!exit){
        exit = true;
        for(int i = 0; i < N; i++){
            r[i] = b[i];
            for(int j = 0; j < N; j++){
                r[i] -= A[i][j] * x[j];
            }
        }
        for(int i = 0; i < N; i++){
            Ar[i] = 0;
            for(int j = 0; j < N; j++){
                Ar[i] += A[i][j] * r[j];
            }
        }
        double rr = 0;
        for(int i = 0; i < N; i++){
            rr += r[i] * r[i];
        }
        double Arr = 0;
        for(int i = 0; i < N; i++){
            Arr += Ar[i] * r[i];
        }
        double t = rr / Arr;
        for(int i = 0; i < N; i++) {
            double tmpx = x[i];
            x[i] += t * r[i];
            if(abs(tmpx - x[i]) > eps){
                exit = false;
            }
        }
    }
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
