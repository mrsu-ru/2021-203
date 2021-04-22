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
            for (int j = 0; j < i; j++) X[i] -= A[i][j] * x[j];
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
    double *r = new double[N];
    double *Ar = new double[N];
    for (int i = 0; i < N; i++) x[i] = 0;
    bool is_continue = true;
    while (is_continue) {
        is_continue = false;

        for (int i = 0; i < N; i++) r[i] = -b[i];

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                r[i] += A[i][j] * x[j];

        for (int i = 0; i < N; i++) {
            Ar[i] = 0;
            for (int j = 0; j < N; j++) Ar[i] += A[i][j] * r[j];
        }

        double t = 0;
        double Ar2 = 0;
        for (int i = 0; i < N; i++) {
            t += Ar[i] * r[i];
            Ar2 += Ar[i] * Ar[i];
        }
        t /= Ar2;
        for (int i = 0; i < N; i++) {
            double temp_x = x[i];
            x[i] = x[i] - t * r[i];
            if (fabs(x[i] - temp_x) > 1e-9) is_continue = true;
        }
    }
    delete[] r;
    delete[] Ar;
}


/**
 * Метод сопряженных градиентов
 */
void utkinnv::lab7() {
    double *r = new double[N];
    double *Ar = new double[N];
    double *prev_x = new double[N];
    double t, a = 1, scalar_r = 0, scalar_Ar = 0;
    bool is_continue = true;
    for (int i = 0; i < N; i++) {
        x[i] = 0;
        r[i] = -b[i];
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            r[i] += A[i][j] * x[j];

    for (int i = 0; i < N; i++) {
        Ar[i] = 0;
        for (int j = 0; j < N; j++) Ar[i] += A[i][j] * r[j];
    }
    for (int i = 0; i < N; i++) {
        scalar_r += r[i] * r[i];
        scalar_Ar += Ar[i] * r[i];
    }
    t = scalar_r / scalar_Ar;
    for (int i = 0; i < N; i++) {
        x[i] = t * b[i];
    }
    while (is_continue) {
        is_continue = false;

        for (int i = 0; i < N; i++) r[i] = -b[i];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                r[i] += A[i][j] * x[j];

        for (int i = 0; i < N; i++) {
            Ar[i] = 0;
            for (int j = 0; j < N; j++) Ar[i] += A[i][j] * r[j];
        }

        double temp_t = t, temp_scalar = scalar_Ar;
        scalar_r = 0;
        scalar_Ar = 0;
        for (int i = 0; i < N; i++) {
            scalar_r += r[i] * r[i];
            scalar_Ar += Ar[i] * r[i];
        }
        t = scalar_r / scalar_Ar;
        a = 1.0 / (1 - (t * scalar_r) / (a * temp_t * temp_scalar));
        for (int i = 0; i < N; i++) {
            double temp_x = x[i];
            x[i] = a * x[i] + (1 - a) * prev_x[i] - t * a * r[i];
            prev_x[i] = temp_x;
            if (fabs(x[i] - temp_x) > 1e-9) is_continue = true;
        }
    }
    delete[] r;
    delete[] Ar;
    delete[] prev_x;
}


void utkinnv::lab8() {
    double **b = new double *[N];
    double t, eps = 0.1;
    for (int i = 0; i < N; ++i) {
        b[i] = new double[N];
    }
    do {
        double phi = 0, max_el = -1e18;
        int max_i, max_j;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (fabs(A[i][j]) > max_el) {
                    max_el = fabs(A[i][j]);
                    max_i = i;
                    max_j = j;
                }
            }
        }
        phi = atan(2 * A[max_i][max_j] / (A[max_j][max_j] - A[max_i][max_i])) / 2;
        double s = sin(phi), c = cos(phi);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                b[i][j] = A[i][j];

        for (int r = 0; r < N; ++r) {
            b[r][max_i] = A[r][max_i] * c - A[r][max_j] * s;
            b[r][max_j] = A[r][max_i] * s + A[r][max_j] * c;
        }
        for (int l = 0; l < N; ++l) {
            A[max_i][l] = b[max_i][l] * c - b[max_j][l] * s;
            A[max_j][l] = b[max_i][l] * s + b[max_j][l] * c;
        }
        A[max_i][max_j] = 0;
        t = 0;
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j)
                t += A[i][j] * A[i][j] + A[j][i] * A[j][i];
    } while (t <= eps);
    for (int i = 0; i < N; ++i) {
        x[i] = A[i][i];

        delete[] b[i];
    }
    delete[] b;
}


void utkinnv::lab9() {
    double eps = 1e-2, l, l_prev;
    double *y = new double[N];
    double *y_prev = new double[N];
    for (int i = 0; i < N; ++i) y_prev[i] = 42;
    do {
        l_prev = l;
        for (int i = 0; i < N; ++i) {
            y[i] = 0;
            for (int j = 0; j < N; ++j) {
                y[i] += A[i][j] * y_prev[j];
            }
        }
        l = (fabs(y[0]) > eps && fabs(y_prev[0]) > eps) ? y[0] / y_prev[0] : 0;
        for (int i = 0; i < N; ++i) {
            y_prev[i] = y[i];
        }
    } while (fabs(l - l_prev) > eps);
    cout << "max lambda = " << l << endl;
    delete[] y;
    delete[] y_prev;
}


std::string utkinnv::get_name() {
    return "Utkin N.V.";
}
