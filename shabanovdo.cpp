#include "shabanovdo.h"

/**
 * Введение в дисциплину
 */
void shabanovdo::lab1()
{
  cout << "hello World!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void shabanovdo::lab2()
{
    int m = N + 1;

    double** arr = new double*[N];
    for (int i = 0; i < N; i++) {
        arr[i] = new double[N + 1];
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = A[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        arr[i][N] = b[i];
    }

//---------прямой ход---------—
    for (int i = 0; i < N; i++) {
        int max = i;
        for (int j = i + 1; j < N; j++) {
            if (abs(arr[j][i]) > abs(arr[max][i]))
                max = j;
        }
        if (max != i) {
            for (int k = 0; k < N + 1; k++) {
                swap(arr[i][k], arr[max][k]);
            }
        }

        double helpel = arr[i][i];
        for (int j = i; j < N + 1; j++) {
            arr[i][j] /= helpel;
        }
        for (int j = i + 1; j < N; j++) {
            helpel = arr[j][i];
            arr[j][i] = 0;
            for (int k = i + 1; k < N + 1; k++)
                arr[j][k] -= arr[i][k] * helpel;
        }
    }

//------------обратный ход---------—
    for (int i = N - 1; i > 0; i--) {
        double h = 0;
        for (int j = i + 1; j < m; j++) {
            double helpel = arr[i - 1][j - 1];
            arr[i - 1][j - 1] = 0;
            h += arr[j - 1][m - 1] * helpel;
        }
        arr[i - 1][m - 1] = arr[i - 1][m - 1] - h;
    }

    for (int i = 0; i < N; i++) {
        x[i] = arr[i][N];
    }
}



/**
 * Метод прогонки
 */
void shabanovdo::lab3()
{
double *alpha = new double[N];
double *betta = new double[N];

alpha[0] = -A[0][1] / A[0][0];
betta[0] = b[0] / A[0][0];

for (int i = 1; i < N - 1; i++) {
alpha[i] = -A[i][i + 1] / (A[i][i - 1] * alpha[i - 1] + A[i][i]);
betta[i] = (-A[i][i - 1] * betta[i - 1] + b[i]) / (A[i][i - 1] * alpha[i - 1] + A[i][i]);
}

betta[N - 1] = (-A[N - 1][N - 2] * betta[N - 2] + b[N - 1]) / (A[N - 1][N - 2] * alpha[N - 2] + A[N - 1][N - 1]);

x[N - 1] = betta[N - 1];

for (int i = N - 2; i >= 0; i--) {
x[i] = betta[i] + alpha[i] * x[i + 1];
} 
}



/**
 * Метод Холецкого
 */
void shabanovdo::lab4()

{
double **help_matrix = new double*[N];
for (int i = 0; i < N; i++)
help_matrix[i] = new double[N];

for(int i = 0; i < N; i++)
for(int j = 0; j < N; j++)
help_matrix[i][j] = 0;

double *d = new double[N];

for(int i = 0; i < N; i++)
{
double tmp = A[i][i];
for(int j = 0; j <= i - 1; j++){
tmp -= d[j] * help_matrix[j][i] * help_matrix[j][i];
}
d[i] = signbit(tmp) == false ? 1 : -1;
help_matrix[i][i]=sqrt(tmp * d[i]);

for(int j = i + 1; j < N; j++)
{
tmp = 0;
for(int k = 0; k <= j - 1; k++)
tmp += d[k] * help_matrix[k][i] * help_matrix[k][j];
help_matrix[i][j] = (A[i][j] - tmp) / (d[i] * help_matrix[i][i]);
}
}
for(int i = 0; i < N; i++){
b[i] /= help_matrix[i][i];
for(int j = i + 1; j < N; j++)
b[j] -= b[i] * help_matrix[i][j];
}
for(int i = 0; i < N; i++)
for(int j = i; j < N; j++)
help_matrix[i][j] *= d[i];

for(int i = N - 1; i >= 0; i--){
b[i] /= help_matrix[i][i];
for(int j = i - 1; j >= 0; j--)
b[j] -= b[i] * help_matrix[j][i];
}
for(int i = 0; i < N; i++)
x[i] = b[i];

}



/**
 * Метод Якоби или Зейделя
 */
void shabanovdo::lab5()
{

    double* prev_x = new double[N];

    while (true) {
        for (int i = 0; i < N; i++)
            prev_x[i] = x[i];

        for (int i = 0; i < N; i++) {
            double sum = 0;

            for (int j = 0; j < i; j++)
                sum += A[i][j] * x[j];

            for (int j = i + 1; j < N; j++)
                sum += A[i][j] * prev_x[j];

            x[i] = (b[i] - sum) / A[i][i];
        }

        double diff = abs(x[0] - prev_x[0]);
        for (int i = 1; i < N; i++){
            if (abs(x[i] - prev_x[i]) > diff)
                diff = abs(x[i] - prev_x[i]);}

        if (diff < 1e-21)
            break;
    }
}



/**
 * Метод минимальных невязок
 */
void shabanovdo::lab6()
{
double* F = new double[N];
    double* r = new double[N];
    double* alfa = new double[N];
    double a, norma, k = 0, ts1, ts2;
    double eps = 1e-19;

    do {
        for (int i = 0; i < N; i++) {
            double tmp = 0;
            for (int j = 0; j < N; j++) {
                tmp += A[i][j] * x[j];
            }
            r[i] = tmp - b[i];
            F[i] = 2 * r[i];
        }

        double* Ar = new double[N];
        for (int i = 0; i < N; i++) {
            double tmps = 0;
            for (int j = 0; j < N; j++) {
                tmps += A[i][j] * r[j];
            }
            Ar[i] = tmps;
        }
        ts1 = 0, ts2 = 0;
        for (int i = 0; i < N; i++) {
            ts1 += Ar[i] * r[i];
            ts2 += Ar[i] * Ar[i];
        }
        a = ts1 / (2 * ts2);

        double*y = new double[N];
        for (int i = 0; i < N; i++)
            y[i] = x[i];

        for (int i = 0; i < N; i++)
            x[i] = x[i] - a * F[i];


        norma = 0;
        for (int i = 0; i < N; i++)
            norma += (y[i] - x[i])*(y[i] - x[i]);


        delete[] y;
        delete[] Ar;
    } while (sqrt(norma) > eps);

}



/**
 * Метод сопряженных градиентов
 */
void shabanovdo::lab7()
{

}


void shabanovdo::lab8()
{
double eps = 1e-20;
double** B = new double* [N];
for (int i = 0; i < N; i++) {
B[i] = new double[N];
}

while (true) {
double norm = 0;
int imax = 0;
int jmax = 1;
for (int i = 0; i < N; i++) {
for (int j = i + 1; j < N; j++) {
if (abs(A[i][j]) > abs(A[imax][jmax])) {
imax = i;
jmax = j;
}
norm += A[i][j] * A[i][j];
}
}

if (sqrt(norm) < eps) {
break;
}

double fi = 0.5 * atan(2 * A[imax][jmax] / (A[imax][imax] - A[jmax][jmax]));

for (int i = 0; i < N; i++) {
B[i][imax] = A[i][imax] * cos(fi) + A[i][jmax] * sin(fi);
B[i][jmax] = A[i][jmax] * cos(fi) - A[i][imax] * sin(fi);
}

for (int i = 0; i < N; i++) {
for (int j = 0; j < N; j++) {
if (j != imax && j != jmax) {
B[i][j] = A[i][j];
}
}
}

for (int j = 0; j < N; j++) {
A[imax][j] = B[imax][j] * cos(fi) + B[jmax][j] * sin(fi);
A[jmax][j] = B[jmax][j] * cos(fi) - B[imax][j] * sin(fi);
}

for (int i = 0; i < N; i++) {
for (int j = 0; j < N; j++) {
if (i != imax && i != jmax) {
A[i][j] = B[i][j];
}
}
}
}

for (int i = 0; i < N; i++) {
x[i] = A[i][i];
}
}
void shabanovdo::lab9() 
{
int n = N;
double *y = new double[n];
double *y_next = new double[n];
double eps =1e-2;
double lyambda = 1;
double lyambda_next = 0;

for(int i = 0; i<n; i++)
y[i] = b[i];

do{
for(int i=0; i<n; i++){
for(int j=0; j<n; j++){
y_next[i] += A[i][j]*y[j];
}
}
lyambda = lyambda_next;

for(int i=0; i<n; i++){
if(y[i]!= 0 && y_next[i] != 0){
lyambda_next = y_next[i]/y[i];
break;
}
}
for (int i=0; i<n; i++)
y[i]=y_next[i];
}while(fabs(lyambda_next - lyambda)>eps);

cout<<"Result: "<<lyambda_next << endl;    
}

std::string shabanovdo::get_name()
{
  return "Shabanov D.O.";
}
