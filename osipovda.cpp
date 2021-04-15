#include "osipovda.h"

/**
 * Введение в дисциплину
 */
void osipovda::lab1() {
    cout << "Hello world!!!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void osipovda::lab2() {
    for (int i = 0; i < N; i++) {
        double mx = A[i][i];
        int mxi = i;
        for (int j = i + 1; j < N; j++) {
            if (fabs(A[j][i]) > mx) {
                mx = fabs(A[j][i]);
                mxi = j;
            }
        }
        swap(A[i], A[mxi]);
        swap(b[i], b[mxi]);
        for (int j = i + 1; j < N; j++) {
            double c = A[j][i] / A[i][i];
            for (int k = i + 1; k < N; k++) {
                A[j][k] -= c * A[i][k];
            }
            A[j][i] = 0;
            b[j] -= c * b[i];
        }
    }

    for (int i = 0; i < N; i++) {
        double c = A[i][i];
        for (int j = i + 1; j < N; j++) {
            A[i][j] /= c;
        }
        b[i] /= c;
        A[i][i] = 1;
    }

    for (int i = N - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            double c = A[j][i];
            A[j][i] = 0;
            b[j] -= c * b[i];
        }
    }

    for (int i = 0; i < N; i++) {
        x[i] = b[i];
    }
}


/**
 * Метод прогонки
 */
void osipovda::lab3() {
    double *alpha = new double[N];
    double *beta = new double[N];

    alpha[0] = A[0][1] / A[0][0];
    beta[0] = b[0] / A[0][0];
    for (int i = 1; i < N; i++) {
        alpha[i] = A[i][i + 1] / (A[i][i] - A[i][i - 1] * alpha[i - 1]);
        beta[i] = (b[i] - A[i][i - 1] * beta[i - 1]) / (A[i][i] - A[i][i - 1] * alpha[i - 1]);
    }

    x[N - 1] = beta[N - 1];
    for (int i = N - 2; i >= 0; i--) {
        x[i] = beta[i] - alpha[i] * x[i + 1];
    }

    delete[]alpha;
    delete[]beta;
}


/**
 * Метод Холецкого
 */
void osipovda::lab4() {
    double **S = new double *[N];
    for (int i = 0; i < N; i++) {
        S[i] = new double[N];
    }
    double *D = new double[N];

    //find S - up triangle
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < i; k++) {
            A[i][i] -= S[k][i] * D[k] * S[k][i];
        }
        D[i] = A[i][i] >= 0 ? 1 : -1;
        S[i][i] = sqrt(D[i] * A[i][i]);
        for (int j = i + 1; j < N; j++) {
            for (int k = 0; k < j; k++) {
                A[i][j] -= S[k][i] * D[k] * S[k][j];
            }
            S[i][j] = A[i][j] / (S[i][i] * D[i]);
        }
    }

    //StDSx=b, StDy = b, find y
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) b[i] -= S[j][i] * D[j] * b[j];
        b[i] /= S[i][i] * D[i];
    }

    //Sx = y, find x
    for (int i = N - 1; i >= 0; i--) {
        for (int k = i + 1; k < N; k++) b[i] -= S[i][k] * x[k];
        x[i] = b[i] / S[i][i];
    }

    for (int i = 0; i < N; i++) {
        delete[] S[i];
    }
    delete[] S;
    delete[] D;
}


/**
 * Метод Якоби или Зейделя
 */
void osipovda::lab5() {
    double *newX = new double[N];
    double eps = 1.e-9;
    bool flag = true;

    for (int i = 0; i < N; i++) x[i] = 1;

    while (flag) {
        flag = false;
        for (int i = 0; i < N; i++) {
            newX[i] = b[i];
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                newX[i] += -A[i][j] * x[j];
            }
            newX[i] /= A[i][i];

            if (!flag && fabs(newX[i] - x[i]) > eps) flag = true;
            x[i] = newX[i];
        }
    }

    delete[] newX;
}


/**
 * Метод минимальных невязок
 */
void osipovda::lab6() {
    double *r = new double[N];
    double *Ar = new double[N];
    double eps = 1.e-9;

    bool flag = true;
    while (flag) {
        flag = false;

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

        double t = 0;
        double Ar_scalar = 0;
        for (int i = 0; i < N; i++) {
            t += Ar[i] * r[i];
            Ar_scalar += Ar[i] * Ar[i];
        }

        t /= Ar_scalar;
        for (int i = 0; i < N; i++) {
            double temp_x = x[i];
            x[i] = x[i] + t * r[i];
            if (fabs(x[i] - temp_x) > eps) {
                flag = true;
            }
        }
    }
    delete[] r;
    delete[] Ar;
}


/**
 * Метод сопряженных градиентов
 */
void osipovda::lab7() {
    double *r = new double[N];
    double *Ar = new double[N];
    double r_scalar_old, r_scalar = 0;
    double t, t_old;
    double alpha_old, alpha = 1;
    double eps = 1.e-18;
    double Ar_scalar = 0;

    r_scalar = 0;
    for (int i = 0; i < N; i++) {
        r[i] = b[i];
        for (int j = 0; j < N; j++) {
            r[i] -= A[i][j] * x[j];
        }
        r_scalar += r[i] * r[i];
    }

    Ar_scalar = 0;
    for (int i = 0; i < N; i++) {
        Ar[i] = 0;
        for (int j = 0; j < N; j++) {
            Ar[i] += A[i][j] * r[j];
        }
        Ar_scalar += Ar[i] * r[i];
    }
    t = r_scalar / Ar_scalar;

    double **E = new double *[N];
    for (int i = 0; i < N; i++) {
        E[i] = new double[N];
        for (int j = 0; j < N; j++) {
            if (i == j) E[i][j] = 1;
            else E[i][j] = 0;
        }
    }
    for (int i = 0; i < N; i++) {
        for  (int j = 0; j < N; j++) {
            E[i][j] -= t * A[i][j];
        }
    }

    double *tb = new double[N];
    for (int i = 0; i < N; i++) {
        tb[i] = t * b[i];
    }

    double *Ex = new double[N];
    for (int i = 0; i < N; i++) {
        Ex[i] = 0;
        for  (int j = 0; j < N; j++) {
            Ex[i] += E[i][j] * x[j];
        }
    }

    for (int i = 0; i < N; i++) {
        x[i] = Ex[i] + tb[i];
    }

    bool flag = true;
    r_scalar_old = r_scalar;
    alpha_old = alpha;
    t_old = t;
    while (flag) {
        flag = false;

        r_scalar = 0;
        for (int i = 0; i < N; i++) {
            r[i] = b[i];
            for (int j = 0; j < N; j++) {
                r[i] -= A[i][j] * x[j];
            }
            r_scalar += r[i] * r[i];
        }

        Ar_scalar = 0;
        for (int i = 0; i < N; i++) {
            Ar[i] = 0;
            for (int j = 0; j < N; j++) {
                Ar[i] += A[i][j] * r[j];
            }
            Ar_scalar += Ar[i] * r[i];
        }
        t = r_scalar / Ar_scalar;

        alpha = 1 - 1./alpha_old * t / t_old * r_scalar / r_scalar_old;
        alpha = 1. / alpha;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) E[i][i] = 1;
                else E[i][j] = 0;
            }
        }

        for (int i = 0; i < N; i++) {
            for  (int j = 0; j < N; j++) {
                E[i][j] -= t * A[i][j];
            }
        }

        for (int i = 0; i < N; i++) {
            tb[i] = alpha * t * b[i];
        }

        for (int i = 0; i < N; i++) {
            Ex[i] = 0;
            for  (int j = 0; j < N; j++) {
                Ex[i] += E[i][j] * x[j];
            }
        }

        for (int i = 0; i < N; i++) {
            Ex[i] *= alpha;
        }

        for (int i = 0; i < N; i++) {
            double temp_x = x[i];
            x[i] = Ex[i] + (1 - alpha) * x[i] + tb[i];
            if (fabs(x[i] - temp_x) > eps) {
                flag = true;
            }
        }

        r_scalar_old = r_scalar;
        alpha_old = alpha;
        t_old = t;
    }
    delete[] r;
    delete[] Ar;
}


void osipovda::lab8() {

}


void osipovda::lab9() {

}


std::string osipovda::get_name() {
    return "Osipov D.A.";
}
