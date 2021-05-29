#include "guskovaim.h"

/**
 * Введение в дисциплину
 */
void guskovaim::lab1()
{
	cout << "Hello world!!!";

}


/**
 * Метод Гаусса с выбором главного элемента
 */
void guskovaim::lab2()
{
    for (int i = 0; i < N; i++) {
        int max = 0;
        for (int j = 0; j < N; j++){
            if (abs(A[max][i])<abs(A[j][i])) max = j;
        }
        swap(A[i], A[max]);
        swap(b[i], b[max]);
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
void guskovaim::lab3()
{
    double *alpha = new double[N];
    double *beta = new double[N];

    double y = A[0][0];
    alpha[0] = -A[0][1] / y;
    beta[0] = b[0] / y;

    for (int i = 1; i < N - 1; i++) {
        y = A[i][i] + A[i][i - 1] * alpha[i - 1];
        alpha[i] = -A[i][i + 1] / y;
        beta[i] = (b[i] - A[i][i - 1] * beta[i - 1]) / y;
    }

    y = A[N - 1][N - 1] + A[N - 1][N - 2] * alpha[N - 2];
    beta[N - 1] = (b[N - 1] - A[N - 1][N - 2] * beta[N - 2]) / y;

    x[N - 1] = beta[N - 1];

    for (int i = N - 2; i >= 0; i--) {
        x[i] = alpha[i] * x[i + 1] + beta[i];
    }
}



/**
 * Метод Холецкого
 */
void guskovaim::lab4()
{
    int i, j, k;
    double **S = new double *[N];
    double *D = new double[N];

    for (i = 0; i < N; i++) {
        S[i] = new double[N];
    }

    for (i = 0; i < N; i++) {
        for (k = 0; k < i; k++) {
            A[i][i] = A[i][i] - S[k][i] * D[k] * S[k][i];
        }
        if (A[i][i] >= 0) {
            D[i] = 1;
        } else D[i] = -1;
        S[i][i] = sqrt(D[i] * A[i][i]);
        for (j = i + 1; j < N; j++) {
            for (k = 0; k < j; k++) {
                A[i][j] = A[i][j] - S[k][i] * D[k] * S[k][j];
            }
            S[i][j] = A[i][j] / (S[i][i] * D[i]);
        }
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < i; j++) {
            b[i] = b[i] - S[j][i] * D[j] * b[j];
        }
        b[i] = b[i] / (S[i][i] * D[i]);
    }

    for (i = N - 1; i > -1; i--) {
        for (int j = i + 1; j < N; j++) {
            b[i] = b[i] - S[i][j] * x[j];
        }
        x[i] = b[i] / S[i][i];
    }

    for (i = 0; i < N; i++) {
        delete[] S[i];
    }

    delete[] S;
    delete[] D;
}



/**
 * Метод Якоби или Зейделя
 */
void guskovaim::lab5() //метод Зейделя
{
    int i, j;

    for (i = 0; i < N; i++) {
        x[i] = 1;
    }

    double *x2 = new double[N];
    bool flag = true;

    while (flag) {
        flag = false;
        for (i = 0; i < N; i++) {
            x2[i] = b[i];
            for (j = 0; j < N; j++) {
                if (i == j) continue;
                x2[i] = x2[i] + x[j] * (-A[i][j]);
            }
            x2[i] = x2[i] / A[i][i];
            if (fabs(x2[i] - x[i]) > 1e-9) {
                flag = true;
            }
            x[i] = x2[i];
        }
    }
    delete[] x2;
}



/**
 * Метод минимальных невязок
 */
void guskovaim::lab6()
{
    double *r = new double[N];
    double *Ar = new double[N];
    bool flag = false;

    for (int i = 0; i < N; i++) {
        x[i] = 0;
    }

    while(!flag){
        flag = true;
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
            if(abs(tmpx - x[i]) > 1e-9){
                flag = false;
            }
        }
    }
}



/**
 * Метод сопряженных градиентов
 */
void guskovaim::lab7()
{
    double *re = new double[N];
    double *Ark = new double[N];
    double *xk = new double[N];
    double x_prev = 0, t = 0, tk = 0, alpha = 1, Sr = 0, SArk = 0, SArk_prev = 0;
    bool flag = false;
    bool first = true;

    for (int i = 0; i < N; i++) {
        x[i] = 0;
        re[i] = 0;
        Ark[i] = 0;
        xk[i] = 0;
    }

    while (!flag) {
        flag = true;
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
            flag = false;
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
            if (fabs(x[i] - x_prev) > 1E-9) flag = false;
        }
    }
    delete[] re;
    delete[] Ark;
    delete[] xk;
}

/**
 * Метод вращения для нахождения собственных значений матрицы
 */
void guskovaim::lab8()
{
    double t = 2;
    int maxi, maxj;
    double **B = new double *[N];
    for (int i = 0; i < N; i++) B[i] = new double[N];

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            if(A[i][j] != A[j][i]) return;
    }

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


void guskovaim::lab9()
{

}


std::string guskovaim::get_name()
{
  return "Guskova I.M.";
}
