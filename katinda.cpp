#include "katinda.h"

/**
 * Введение в дисциплину
 */
void katinda::lab1()
{
    cout << "Hello world!";
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void katinda::lab2()
{
    for(int i = 0; i < N; i++){
        int mx = i;
        for(int j = i + 1; j < N; j++){
            if(abs(A[i][j]) > abs(A[i][mx])){
                mx = j;
            }
        }
        swap(A[i], A[mx]);
        swap(b[i], b[mx]);
        for(int j = i + 1; j < N; j++){
            double c = A[j][i]/A[i][i];
            for(int k = i; k < N; k++){
                A[j][k] -= c*A[i][k];
            }
            b[j] -= c*b[i];
        }
    }
    for(int i = 0; i < N; i++){
        double c = A[i][i];
        for(int j = i; j < N; j++){
            A[i][j] /= c;
        }
        b[i] /= c;
    }
    x[N - 1] = b[N - 1];
    for(int i = N - 2; i >= 0; i--){
        x[i] = b[i];
        for(int j = i + 1; j < N; j++){
            x[i] -= A[i][j]*x[j];
        }
    }
}



/**
 * Метод прогонки
 */
void katinda::lab3()
{
    double* alpha = new double[N];
    double* beta = new double[N];
    alpha[0] = -A[0][1] / A[0][0];
    beta[0] = b[0] / A[0][0];
    for(int i = 1; i < N; i++){
        alpha[i] = -A[i][i + 1] / (A[i][i] + A[i][i - 1] * alpha[i - 1]);
        beta[i] = (b[i] - A[i][i - 1] * beta[i - 1]) / (A[i][i] + A[i][i - 1] * alpha[i - 1]);
    }
    x[N - 1] = beta[N - 1];
    for(int i = N - 2; i >= 0; i--){
        x[i] = alpha[i] * x[i + 1] + beta[i];
    }
}



/**
 * Метод Холецкого
 */
void katinda::lab4()
{
    double** S = new double*[N];
    double* D = new double[N];
    for(int i = 0; i < N; i++){
        S[i] = new double[N];
    }
    for(int i = 0; i < N; i++){
        for(int j = i; j < N; j++){
            if(i == j){
                double c = A[i][i];
                for(int k = 0; k < i; k++){
                    c -= S[k][i] * D[k] * S[k][j];
                }
                if(c >= 0)
                    D[i] = 1;
                else
                    D[i] = -1;
                S[i][i] = sqrt(D[i]*c);
            }
            else{
                double c = A[i][j];
                for(int k = 0; k < i; k++){
                    c -= S[k][i] * D[k] * S[k][j];
                }
                S[i][j] = c / (S[i][i] * D[i]);
            }
        }
    }
    double** StD = new double*[N];
    for(int i = 0; i < N; i++)
        StD[i] = new double[N];
    for(int i = 0; i < N; i++){
        for(int j = 0; j <= i; j++){
            StD[i][j] = S[j][i] * D[i];
        }
    }
    double* Y = new double[N];
    Y[0] = b[0] / StD[0][0];
    for(int i = 1; i < N; i++){
        double c = b[i];
        for(int j = 0; j < i; j++){
            c -= StD[i][j] * Y[j];
        }
        Y[i] = c / StD[i][i];
    }
    x[N - 1] = Y[N - 1] / S[N - 1][N - 1];
    for(int i = N - 2; i >= 0; i--){
        double c = Y[i];
        for(int j = N - 1; j > i; j--){
            c -= S[i][j] * x[j];
        }
        x[i] = c / S[i][i];
    }
}



/**
 * Метод Якоби или Зейделя
 */
void katinda::lab5()
{
    double eps = 1e-9;
    for(int i = 0; i < N; i++){
        x[i] = b[i];
    }
    bool exit = false;
    while(!exit){
        exit = true;
        for(int i = 0; i < N; i++){
            double tmpx = b[i];
            for(int j = 0; j < N; j++){
                if(i == j)
                    continue;
                tmpx -= A[i][j] * x[j];
            }
            tmpx /= A[i][i];
            if(abs(x[i] - tmpx) > eps)
                exit = false;
            x[i] = tmpx;
        }
    }
}



/**
 * Метод минимальных невязок
 */
void katinda::lab6()
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
        double tau = rr / Arr;
        for(int i = 0; i < N; i++) {
            double tmpx = x[i];
            x[i] += tau * r[i];
            if(abs(tmpx - x[i]) > eps){
                exit = false;
            }
        }
    }
}



/**
 * Метод сопряженных градиентов
 */
void katinda::lab7() {
    double eps = 1e-10;
    double *r = new double[N];
    double *Ar = new double[N];
    double *prev_x = new double[N];
    bool exit = false;
    bool first = true;
    double alpha = 1;
    double tau, prev_rr, prev_tau;
    for (int i = 0; i < N; i++) {
        x[i] = 0;
        prev_x[i] = 0;
    }
    while (!exit) {
        exit = true;
        for (int i = 0; i < N; i++) {
            r[i] = b[i];
            for (int j = 0; j < N; j++) {
                r[i] -= A[i][j] * x[j];
            }
        }
        for (int i = 0; i < N; i++) {
            Ar[i] = 0;
            for (int j = 0; j < N; j++) {
                Ar[i] += A[i][j] * r[j];
            }
        }
        double rr = 0;
        for (int i = 0; i < N; i++) {
            rr += r[i] * r[i];
        }
        double Arr = 0;
        for (int i = 0; i < N; i++) {
            Arr += Ar[i] * r[i];
        }
        tau = rr / Arr;
        if (first) {
            for (int i = 0; i < N; i++) {
                x[i] = tau * b[i];
            }
            first = false;
            prev_rr = rr;
            prev_tau = tau;
            exit = false;
            continue;
        }
        alpha = 1 / (1 - (tau * rr) / (alpha * prev_tau * prev_rr));
        for (int i = 0; i < N; i++) {
            double tmpx = x[i];
            x[i] = alpha * x[i] + (1 - alpha) * prev_x[i] - tau * alpha * r[i];
            prev_x[i] = tmpx;
            if (abs(tmpx - x[i]) > eps) {
                exit = false;
            }
        }
        prev_rr = rr;
        prev_tau = tau;
    }
}


void katinda::lab8()
{
    double eps = 1e-9;
    double t = 1;
    double** B = new double* [N];
    for(int i = 0; i < N; i++)
        B[i] = new double[N];
    while(t > eps){
        int ii = 1, jj = 0;
        for(int i = 0; i < N; i++)
            for(int j = 0; j < i; j++)
                if(abs(A[i][j]) > abs(A[ii][jj])){
                    ii = i;
                    jj = j;
                }
        double phi = 0.5 * atan(2 * A[ii][jj] / (A[ii][ii] - A[jj][jj]));
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                B[i][j] = A[i][j];
        for(int i = 0; i < N; i++){
            B[i][ii] = A[i][ii] * cos(phi) + A[i][jj] * sin(phi);
            B[i][jj] = A[i][jj] * cos(phi) - A[i][ii] * sin(phi);
        }
        for(int i = 0; i < N; i++){
            A[i][ii] = B[i][ii];
            A[i][jj] = B[i][jj];
        }
        for(int i = 0; i < N; i++){
            A[ii][i] = B[ii][i] * cos(phi) + B[jj][i] * sin(phi);
            A[jj][i] = B[jj][i] * cos(phi) - B[ii][i] * sin(phi);
        }
        t = 0;
        for(int i = 0; i < N; i++)
            for(int j = 0; j < i; j++) {
                t += A[i][j] * A[i][j];
            }
        t *= 2;
    }
    for(int i = 0; i < N; i++)
        x[i] = A[i][i];
}


void katinda::lab9()
{
    double eps = 1e-3;
    double *y = new double[N];
    double *prev_y = new double[N];
    double eigenvalue;
    for(int i = 0; i < N; i++)
        prev_y[i] = 1;
    while(true){
        for(int i = 0; i < N; i++){
            double sum = 0;
            for(int j = 0; j < N; j++){
                sum += A[i][j] * prev_y[j];
            }
            y[i] = sum;
        }
        double tmp = eigenvalue;
        for(int i = 0; i < N; i++) {
            if(abs(y[i]) > eps && abs(prev_y[i]) > eps){
                eigenvalue = y[i] / prev_y[i];
                break;
            }
        }
        if(abs(eigenvalue - tmp) < eps){
            break;
        }
        for(int i = 0; i < N; i++){
            prev_y[i] = y[i];
        }
    }
    cout << "Maximum eigenvalue = " << eigenvalue;
}


std::string katinda::get_name()
{
  return "Katin D.A.";
}
