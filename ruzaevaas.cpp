#include "ruzaevaas.h"

/**
 * Введение в дисциплину
 */
void ruzaevaas::lab1()
{
  cout << "hello world!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void ruzaevaas::lab2()
{
double** arr_help = new double*[N];
    for (int i = 0; i < N; i++)
        arr_help[i] = new double[N + 1];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            arr_help[i][j] = A[i][j];
    }

    for (int i = 0; i < N; i++)
        arr_help[i][N] = b[i];

    for (int i = 0; i < N; i++) {
        int max = i;
        for (int j = i + 1; j < N; j++) {
            if (abs(arr_help[j][i]) > abs(arr_help[max][i]))
                max = j;
        }
        if (max != i) {
            for (int k = 0; k < N + 1; k++)
                swap(arr_help[i][k], arr_help[max][k]);
        }

        double helpel = arr_help[i][i];
        for (int j = i; j < N + 1; j++)
            arr_help[i][j] /= helpel;

        for (int j = i + 1; j < N; j++) {
            helpel = arr_help[j][i];
            arr_help[j][i] = 0;
            for (int k = i + 1; k < N + 1; k++)
                arr_help[j][k] -= arr_help[i][k] * helpel;
        }
    }
    int n = N + 1;
    for (int i = N - 1; i > 0; i--) {
        double h = 0;
        for (int j = i + 1; j < n; j++) {
            double help_el = arr_help[i - 1][j - 1];
            arr_help[i - 1][j - 1] = 0;
            h += arr_help[j - 1][n - 1] * help_el;
        }
        arr_help[i - 1][n - 1] = arr_help[i - 1][n - 1] - h;
    }

    for (int i = 0; i < N; i++)
        x[i] = arr_help[i][N];

}



/**
 * Метод прогонки
 */
void ruzaevaas::lab3()
{
double *first = new double[N];
    double *second = new double[N];

    first[0] = -A[0][1] / A[0][0];
    second[0] = b[0] / A[0][0];

    for (int i = 1; i < N - 1; i++) {
        first[i] = -A[i][i + 1] / (A[i][i - 1] * first[i - 1] + A[i][i]);
        second[i] = (-A[i][i - 1] * second[i - 1] + b[i]) / (A[i][i - 1] * first[i - 1] + A[i][i]);
    }

    second[N - 1] = (-A[N - 1][N - 2] * second[N - 2] + b[N - 1]) / (A[N - 1][N - 2] * first[N - 2] + A[N - 1][N - 1]);

    x[N - 1] = second[N - 1];

    for (int i = N - 2; i >= 0; i--) {
        x[i] = second[i] + first[i] * x[i + 1];
    }
}



/**
 * Метод Холецкого
 */
void ruzaevaas::lab4()
{
 int *D = new int[N];
    double **S = new double*[N];
    for (int i = 0; i < N; i++){
        S[i] = new double[N];
        for (int j = 0; j < N; j++)
            S[i][j] = 0;
    }
    double tmp;
    for (int i = 0; i < N; i++){
        tmp = A[i][i];
        for (int j = 0; j < i; j++) tmp -= D[j]*pow(S[j][i], 2);

        if (tmp > 0) D[i] = 1;
        else D[i] =- 1;

        S[i][i] = sqrt(D[i] * tmp);
        double tmp_two;
        for (int j=i+1; j<N; j++){
            tmp_two = A[i][j];
            for (int k=0; k<j; k++) tmp_two -= D[k] * S[k][i] * S[k][j];
            S[i][j] = tmp_two / (D[i] * S[i][i]);
        }
    }

    double *y;
    y = new double[N];
    y[0] = b[0]/S[0][0];

    for (int i = 1; i < N; i++){
        for (int j = i; j < N; j++) b[j] -= S[i-1][j]*y[i-1];
        y[i] = b[i]/S[i][i];
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            S[i][j] *= D[i];

    x[N-1] = y[N-1]/S[N-1][N-1];

    for (int i = N - 2; i >= 0; i--){
        for (int j = i ; j >= 0; j--) y[j] -= S[j][i+1]*x[i+1];
        x[i] = y[i]/S[i][i];
    }
}



/**
 * Метод Якоби или Зейделя
 */
void ruzaevaas::lab5()
{

}



/**
 * Метод минимальных невязок
 */
void ruzaevaas::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void ruzaevaas::lab7()
{

}


void ruzaevaas::lab8()
{
    double **b = new double *[N];
    double t, eps = 1;
    for (int i = 0; i < N; ++i) {
        b[i] = new double[N];
    }
    do {
        double max_el = 1e-18;
        int max_i, max_j;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i == j) continue;
                if (fabs(A[i][j]) > max_el) {
                    max_el = fabs(A[i][j]);
                    max_i = i;
                    max_j = j;
                }
            }
        }
        double phi = atan(2 * A[max_i][max_j] / (A[max_j][max_j] - A[max_i][max_i])) / 2;
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
    } while (t > eps);
    for (int i = 0; i < N; ++i) {
        x[i] = A[i][i];
        delete[] b[i];
    }
    delete[] b;
}


void ruzaevaas::lab9()
{

}


std::string ruzaevaas::get_name()
{
  return "Ruzaeva A.S.";
}
