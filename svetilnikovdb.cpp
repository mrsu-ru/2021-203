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
void svetilnikovdb::lab7()
{
    double *re = new double[N];
    double *Ark = new double[N];
    double *xk = new double[N];
    double x_prev = 0, t = 0, tk = 0, alpha = 1, Sr = 0, SArk = 0, SArk_prev = 0;
    bool exit = false;
    bool first = true;
    for (int i = 0; i < N; i++) {
        x[i] = 0;
        re[i] = 0;
        Ark[i] = 0;
        xk[i] = 0;
    }
    while (!exit) {
        exit = true;
        for (int i = 0; i < N; i++) {
            re[i] = b[i];
            for (int j = 0; j < N; j++) {
                re[i] -= A[i][j] * x[j];
            }
        }
        for (int i = 0; i < N; i++) {
            Ark[i] = 0;
            for (int j = 0; j < N; j++) Ark[i] += A[i][j] * re[j];
        }
        if (first) {
            first = false;
            exit = false;
            for (int i = 0; i < N; i++) {
                Sr += re[i] * re[i];
                SArk += Ark[i] * re[i];
            }
            t = Sr / SArk;
            for (int i = 0; i < N; i++) {
                x[i] = t * b[i];
            }
        }
        tk = t, SArk_prev = SArk;
        Sr = 0;
        SArk = 0;
        for (int i = 0; i < N; i++) {
            Sr += re[i] * re[i];
            SArk += Ark[i] * re[i];
        }
        t = Sr / SArk;
        alpha = 1.0 / (1 - (t * Sr) / (alpha * tk * SArk_prev));
        for (int i = 0; i < N; i++) {
            x_prev = x[i];
            x[i] = t * alpha * re[i] + alpha * x[i] + (1 - alpha) * xk[i];
            xk[i] = x_prev;
            if (fabs(x[i] - x_prev) > 1E-9) exit = false;
        }
    }
    delete[] re;
    delete[] Ark;
    delete[] xk;
}



/**
 * Метод вращения для нахождения собственных значений матрицы
 */
void svetilnikovdb::lab8()
{
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            if(A[i][j] != A[j][i]) return;
    }
    double **B = new double *[N];
    double t = 2;
    int maxi, maxj;
    for (int i = 0; i < N; i++) B[i] = new double[N];
    while (t > 1) {
        maxi = 0, maxj = 1;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                if (fabs(A[i][j]) > fabs(A[maxi][maxj])) {
                    maxi = i;
                    maxj = j;
                }
            }
        }
        double phi = atan(2 * A[maxi][maxj] / (-A[maxi][maxi] + A[maxj][maxj])) / 2;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) B[i][j] = A[i][j];
        }
        for (int r = 0; r < N; r++) {
            B[r][maxi] = A[r][maxi] * cos(phi) - A[r][maxj] * sin(phi);
            B[r][maxj] = A[r][maxi] * sin(phi) + A[r][maxj] * cos(phi);
        }
        for (int c = 0; c < N; c++) {
            A[maxi][c] = B[maxi][c] * cos(phi) - B[maxj][c] * sin(phi);
            A[maxj][c] = B[maxi][c] * sin(phi) + B[maxj][c] * cos(phi);
        }
        A[maxi][maxj] = 0;
        t = 0;
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++)
                t += A[i][j] * A[i][j] + A[j][i] * A[j][i];
        }
    }
    for (int i = 0; i < N; i++) x[i] = A[i][i];
    for (int i = 0; i < N; i++) delete[] B[i];
    delete[] B;
}



/**
 * Нахождение наибольшего по модулю собственного значения матрицы.
 */
void svetilnikovdb::lab9()
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            if (A[i][j] != A[j][i]) return;
    }
    double l, maxl = 0;
    bool cont = true;
    double *y = new double[N];
    double *y_prev = new double[N];
    for (int i = 0; i < N; i++) y_prev[i] = 1;
    while (cont) {
        cont = false;
        for (int i = 0; i < N; i++) {
            y[i] = 0;
            for (int j = 0; j < N; j++) {
                y[i] += A[i][j] * y_prev[j];
            }
        }
        l = 0;
        for (int i = 0; i < N; i++) {
            if (fabs(y[i]) > 1E-3 && fabs(y_prev[i]) > 1E-3) {
                l = y[i] / y_prev[i];
                break;
            }
        }
        if (fabs(l - maxl) > 1E-3) cont = true;
        maxl = l;
        for (int i = 0; i < N; i++) y_prev[i] = y[i];
    }
    cout << "The largest lambda: " << maxl << endl;
    delete[] y;
    delete[] y_prev;
}


std::string svetilnikovdb::get_name()
{
  return "Svetilnikov D.B.";
}
