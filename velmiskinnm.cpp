#include "velmiskinnm.h"

/**
 * Введение в дисциплину
 */
void velmiskinnm::lab1()
{
  cout << "HELLO, WORLD!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void velmiskinnm::lab2(){
    int rows = N;

    for (int i = 0; i < rows; i++){
        int maxElement = i;
        for (int j = i + 1; j < rows; j++){
            if (A[j][i] > A[maxElement][i])
                maxElement = j;
        }
        for (int k = 0; k < rows; k++){
            swap(A[maxElement][k], A[i][k]);
        }
        swap(b[maxElement], b[i]);


        double first = A[i][i];
        for (int j = i; j < rows; j++){
            A[i][j] /= first;
        }

        b[i] /= first;
        for (int j = i + 1; j < rows; j++){
            first = A[j][i];

            for (int k = i; k < rows; k++){
                A[j][k] -= A[i][k] * first;
            }
            b[j] -= b[i] * first;
        }
    }

    for (int i = rows; i >= 0; i--){
        for (int j = i + 1; j < rows; j++){
            b[i] += -A[i][j] * x[j];
            A[i][j] = 0;
        }
        x[i] = b[i];
    }
}



/**
 * Метод прогонки
 */
void velmiskinnm::lab3()
{
    double y1, alpha[N], beta[N];
    int N1 = N-1;
    y1 = A[0][0];
    alpha[0] = -A[0][1] / y1;
    beta[0] = b[0] / y1  ;
    for (int i = 1; i < N; i++) {
        y1 = A[i][i] + A[i][i - 1] * alpha[i - 1];
        alpha[i] = -A[i][i + 1] / y1;
        beta[i] = (b[i] - A[i][i - 1] * beta[i - 1]) / y1;
    }
    x[N1] = beta[N1];

    for (int i = N1 - 1; i >= 0; i--) {
        x[i] = alpha[i] * x[i + 1] + beta[i];
    }
}



/**
 * Метод Холецкого
 */
void velmiskinnm::lab4()
{
    double** S = new double*[N];
    for(int i = 0; i < N; i++){
        S[i] = new double[N];
    }

    double* D = new double[N];
    //первый этап - поиск LU-разложения
    //начальная инициализация массива вспомогательных сумм

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
    double* y = new double[N];
    //второй этап - поиск корней
    y[0] = b[0] / StD[0][0];

    ///Ly = b
    for(int i = 1; i < N; i++){
        double c = b[i];

        for(int j = 0; j < i; j++){
            c -= StD[i][j] * y[j];
        }
        y[i] = c / StD[i][i];
    }

    //Sx = y
    x[N - 1] = y[N - 1] / S[N - 1][N - 1];
    for(int i = N - 2; i >= 0; i--){
        double c = y[i];
        for(int j = N - 1; j > i; j--){
            c -= S[i][j] * x[j];
        }
        x[i] = c / S[i][i];
    }
}



/**
 * Метод Якоби или Зейделя
 */
void velmiskinnm::lab5()
{
    double eps = 1e-21;
    for(int i = 0; i < N; i++){
        x[i] = b[i];
    }
    bool exit = false;
    while(!exit){
        exit = true;
        for(int i = 0; i < N; i++){
            double temp_x = b[i];
            for(int j = 0; j < N; j++){
                if(i == j)
                    continue;
                temp_x -= A[i][j] * x[j];
            }
            temp_x /= A[i][i];
            if(abs(x[i] - temp_x) > eps)
                exit = false;
            x[i] = temp_x;
        }
    }
}



/**
 * Метод минимальных невязок
 */
void velmiskinnm::lab6()
{
    double eps = 1e-21;
    double *y = new double[N];
    double *num = new double[N];

    bool exit = false;

    for (int i = 0; i < N; i++)
        x[i] = 0;
    while(!exit){
        exit = true;

        for(int i = 0; i < N; i++){
            y[i] = b[i];
            for(int j = 0; j < N; j++){
                y[i] -= A[i][j] * x[j];
            }
        }
        for(int i = 0; i < N; i++){
            num[i] = 0;
            for(int j = 0; j < N; j++){
                num[i] += A[i][j] * y[j];
            }
        }
        double den = 0;
        for(int i = 0; i < N; i++){
            den += y[i] * y[i];
        }
        double result = 0;
        for(int i = 0; i < N; i++){
            result += num[i] * y[i];
        }
        double tau = den / result;
        for(int i = 0; i < N; i++) {
            double tmpx = x[i];
            x[i] += tau * y[i];
            if(abs(tmpx - x[i]) > eps){
                exit = false;
            }
        }
    }
}



/**
 * Метод сопряженных градиентов
 */
void velmiskinnm::lab7()
{
    double eps = 1e-20;
    double *r = new double[N];
    double *num = new double[N];
    double *prev_x = new double[N];
    bool exit = false;
    bool first = true;
    double alpha = 1;

    double tau, add_den, add_tau;
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
            num[i] = 0;
            for (int j = 0; j < N; j++) {
                num[i] += A[i][j] * r[j];
            }
        }
        double den = 0;
        for (int i = 0; i < N; i++) {
            den += r[i] * r[i];
        }
        double result = 0;
        for (int i = 0; i < N; i++) {
            result += num[i] * r[i];
        }

        tau = den / result;
        if (first) {
            for (int i = 0; i < N; i++) {
                x[i] = tau * b[i];
            }
            first = false;
            add_den = den;
            add_tau = tau;
            exit = false;
            continue;
        }
        alpha = 1 / (1 - (tau * den) / (alpha * add_tau * add_den));
        for (int i = 0; i < N; i++) {
            double tmpx = x[i];
            x[i] = alpha * x[i] + (1 - alpha) * prev_x[i] - tau * alpha * r[i];
            prev_x[i] = tmpx;
            if (abs(tmpx - x[i]) > eps) {
                exit = false;
            }
        }
        add_den = den;
        add_tau = tau;
    }

}


void velmiskinnm::lab8()
{

}


void velmiskinnm::lab9()
{
    double eps = 1e-3;
    double *y = new double[N];
    double *prev_y = new double[N];
    double totalValue;
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
        double tmp = totalValue;
        for(int i = 0; i < N; i++) {
            if(abs(y[i]) > eps && abs(prev_y[i]) > eps){
                totalValue = y[i] / prev_y[i];
                break;
            }
        }
        if(abs(totalValue - tmp) < eps){
            break;
        }
        for(int i = 0; i < N; i++){
            prev_y[i] = y[i];
        }
    }
    std::cout << "Total value === " << totalValue;
}


std::string velmiskinnm::get_name()
{
  return "Velmiskin N.M.";
}
