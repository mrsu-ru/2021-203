#include "svetilnikovdb.h"

/**
 * Введение в дисциплину
 */
void svetilnikovdb::lab1()
{
  cout << "Hello world!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void svetilnikovdb::lab2()
{
    for (int i = 0; i < N; i++) {
        int ma = 0;
        for (int j = 0; j < N; j++){
            if (abs(A[ma][i])<abs(A[j][i])) ma = j;
        }
        swap(A[i], A[ma]);
        swap(b[i], b[ma]);
        for (int j = i + 1; j < N; j++) {
            double c = A[j][i] / A[i][i];
            for (int k = i + 1; k < N; k++){
                A[j][k] -= c * A[i][k];
            }
            b[j] -= c * b[i];
            A[j][i] = 0;
        }
    }
    for(int i = 0; i < N; i++){
        double d = A[i][i];
        for(int j = 0; j < N; j++){
            A[i][j]/= d;
        }
        b[i]/=d;
    }
    for (int i = N - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < N; j++) x[i] -= A[i][j] * x[j];
    }
}



/**
 * Метод прогонки
 */
void svetilnikovdb::lab3()
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
void svetilnikovdb::lab4()
{
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            if(A[i][j] != A[j][i]) return;
    }
    double* D = new double[N];
    double** S = new double*[N];
    double sds = 0;
    for(int i = 0; i < N; i++) S[i] = new double[N];
    for(int i = 0; i < N; i++){
        sds = 0;
        for(int kd = 0; kd < i; kd++) sds += S[kd][i] * D[kd] * S[kd][i];
        if(A[i][i] - sds < 0) D[i] = -1;
        else D[i] = 1;
        S[i][i] = sqrt(fabs(A[i][i] - sds));
        for(int j = i + 1; j < N; j++){
            sds = 0;
            for(int k = 0; k < j; k++) sds += S[k][i] * D[k] * S[k][j];
            S[i][j] = (A[i][j] - sds) / (S[i][i] * D[i]);
        }
    }
    double* y = new double[N];
    for(int i = 0; i < N; i++) {
        y[i] = b[i];
        for (int j = 0; j < i; j++) y[i] -= S[j][i] * D[j] * y[j];
        y[i] /= S[i][i] * D[i];
    }
    for(int i = N - 1; i >= 0; i--){
        for(int j = i + 1; j < N; j++) y[i] -= S[i][j] * x[j];
        x[i] = y[i] / S[i][i];
    }
    for(int i = 0; i < N; i++) delete[] S[i];
    delete[] S;
    delete[] D;
    delete[] y;
}



/**
 * Метод Якоби или Зейделя
 */
void svetilnikovdb::lab5()
{
    bool exit = false;
    double ix = 0;
    for (int i = 0; i < N; i++) x[i] = 0;
    while(exit == false){
        exit = true;
        for(int i = 0; i < N; i++){
            ix = b[i];
            for(int j = 0; j < N; j++){
                if(i != j) {
                    ix -= A[i][j] * x[j];
                }
            }
            ix /= A[i][i];
            if(fabs(ix - x[i]) > 1E-9) exit = false;
            x[i] = ix;
        }
    }
}



/**
 * Метод минимальных невязок
 */
void svetilnikovdb::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void svetilnikovdb::lab7()
{

}


void svetilnikovdb::lab8()
{

}


void svetilnikovdb::lab9()
{

}


std::string svetilnikovdb::get_name()
{
  return "Svetilnikov D.B.";
}
