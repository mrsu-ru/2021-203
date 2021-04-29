#include "taynovaa.h"

/**
 * Введение в дисциплину
 */
void taynovaa::lab1() {
    cout << "hello world!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void taynovaa::lab2() {
    for (int i = 0; i < N; i++) {
        int index_max = i;

        for (int m = i; m < N; m++) {
            if (fabs(A[index_max][i]) < fabs(A[m][i]))
                index_max = m;
        }

        swap(A[index_max], A[i]);
        swap(b[index_max], b[i]);

        for (int j = i + 1; j < N; j++) {
            double c = A[j][i] / A[i][i];
            for (int k = i; k < N; k++) {
                A[j][k] -= c * A[i][k];
            }
            b[j] -= c * b[i];
        }
    }
// обратный
    for (int i = N - 1; i >= 0; i--) {
        double c = 0;
        for (int j = i + 1; j < N; j++) {
            c += A[i][j] * x[j];
        }
        x[i] = (b[i] - c) / A[i][i];
    }
}


/**
 * Метод прогонки
 */
void taynovaa::lab3() {
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


void taynovaa::lab4() {
    double **S = new double *[N];
    double *D = new double[N];
    for (int i = 0; i < N; i++) S[i] = new double[N];

    for (int i = 0; i < N; i++) {
        double s = 0;
        for (int k = 0; k < i; k++) s += S[k][i] * S[k][i] * D[k];
        D[i] = (A[i][i] - s < 0 ? -1 : 1);
        S[i][i] = sqrt(abs(A[i][i] - s));

        for (int j = i + 1; j < N; j++) {
            s = 0;
            for (int k = 0; k < j; k++) s += S[k][i] * S[k][j] * D[k];
            S[i][j] = (A[i][j] - s) / (S[i][i] * D[i]);
        }
    }

//    StD y = b
    double *y = new double[N];
    for (int i = 0; i < N; i++) {
        double s = 0;
        for (int k = 0; k < i; k++) s += S[k][i] * D[k] * y[k];
        y[i] = (b[i] - s) / (S[i][i] * D[i]);
    }
//    Sx = y
    for (int i = N - 1; i >= 0; i--) {
        for (int k = i + 1; k < N; k++) y[i] -= S[i][k] * x[k];
        x[i] = y[i] / S[i][i];
    }
}

/**
 * Метод Якоби или Зейделя
 */

void taynovaa::lab5() {
    double eps = 1e-18;
    for (int i = 0; i < N; i++) x[i] = 0;
    bool notOk = 1;
    while (notOk) {
        notOk = 0;
        for (int i = 0; i < N; i++) {
            double tmp = b[i];
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                tmp -= A[i][j] * x[j];
            }
            tmp /= A[i][i];
            if (abs(tmp - x[i]) > eps) notOk = 1;
            x[i] = tmp;
        }
    }
}

/**
 * Метод минимальных невязок
 */
double SP(double *a, double *b, int N) {
    double t = 0;
    for (int i = 0; i < N; i++) {
        t += a[i] * b[i];
    }
    return t;
}

void taynovaa::lab6() {
    double *r = new double[N];
    double *Ar = new double[N];
    bool go = 1;

    for (int i = 0; i < N; i++) x[i] = 0;
    while (go) {
        go = 0;
        for (int i = 0; i < N; i++) r[i] = b[i] - SP(A[i], x, N);

        for (int i = 0; i < N; i++) Ar[i] = SP(A[i], r, N);

        double t = SP(Ar, r, N) / SP(Ar, Ar, N);

        for (int i = 0; i < N; i++) {
            double prev_x = x[i];
            x[i] += t * r[i];
            if (fabs(prev_x - x[i]) > 1e-18) go = 1;
        }
    }
}


/**
 * Метод сопряженных градиентов
 */
void taynovaa::lab7() {
    double *r = new double[N];
    double *Ar = new double[N];
    double *xp = new double[N];
    double t = 0;
    bool go = 1;
    fill(x, x + N, 0);

    for (int i = 0; i < N; i++) r[i] = b[i] - SP(A[i], x, N);
    for (int i = 0; i < N; i++) Ar[i] = SP(A[i], r, N);

    double sr = SP(r, r, N);
    double sAr = SP(Ar, r, N);
    t = sr / sAr;

    for (int i = 0; i < N; i++) x[i] += t * r[i];

    double sArp = sAr;
    double alpha = 1;

    while (go) {
        go = false;
        for (int i = 0; i < N; i++) r[i] = b[i] - SP(A[i], x, N);
        for (int i = 0; i < N; i++) Ar[i] = SP(A[i], r, N);
        sr = SP(r, r, N);
        sAr = SP(Ar, r, N);
        t = sr / sAr;
        alpha = 1. / (1 - (t * sr) / (alpha * t * sArp));
        for (int i = 0; i < N; i++) {
            double xpp = x[i];
            x[i] = t * alpha * r[i] + alpha * x[i] + (1 - alpha) * xp[i];
            xp[i] = xpp;
            if (fabs(x[i] - xp[i]) > 1e-18) go = true;
        }
    }
}


void taynovaa::lab8() {

}


void taynovaa::lab9() {

}


std::string taynovaa::get_name() {
    return "Taynov A. A.";
}
