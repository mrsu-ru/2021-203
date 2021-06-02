#include "gladyshevadn.h"

/**
 * Введение в дисциплину
 */
void gladyshevadn::lab1()
{
	cout << "Hello, world!";
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void gladyshevadn::lab2()
{
    for (int i = 0; i < N; i++){
        int maxi = i;
        for (int j = i + 1; j < N; j++){
            if (abs(A[j][i]) > abs(A[maxi][i])) maxi = j;
        }
        if (maxi != i){
            swap(A[i], A[maxi]);
            swap(b[i], b[maxi]);
        }
        for (int j = i + 1; j < N; j++){
            double coeff = A[j][i] / A[i][i];
            for (int k = i + 1; k < N; k++) A[j][k] -= (coeff * A[i][k]);
            A[j][i] = 0;
            b[j] -= (coeff * b[i]);
        }
    }
    for (int i=N-1; i>=0; i--){
        for (int j=i+1; j<N; j++) b[i] -= (A[i][j] * x[j]);
        x[i] = b[i] / A[i][i];
        A[i][i] = 1;
    }
}



/**
 * Метод прогонки
 */
void gladyshevadn::lab3()
{
    double* alpha = new double[N];
    double* beta = new double[N];

    // A[0][0](x0) + A[0][1](x1) = b[0]
    // x0 = alpha[0](x1) + beta[0]

    alpha[0] = -A[0][1] / A[0][0];
    beta[0] = b[0] / A[0][0];
    for (int i = 1; i < N; i++){
        alpha[i] = -A[i][i+1] / (A[i][i] + A[i][i-1] * alpha[i-1]);
        beta[i] = (b[i] - A[i][i-1] * beta[i-1]) / (A[i][i] + A[i][i-1] * alpha[i-1]);
    }
    x[N-1] = beta[N-1];
    for (int i=N-2; i>=0; i--){
        x[i] = alpha[i] * x[i+1] + beta[i];
    }

    delete[]alpha;
    delete[]beta;
}



/**
 * Метод Холецкого
 */
void gladyshevadn::lab4()
{
    double** S = new double*[N];
    for (int i=0; i<N; i++) S[i] = new double[N];
    double* D = new double[N];
    // S
    for (int i=0; i<N; i++){
        for (int j=i; j<N; j++){
            if (j==i){
                for (int l=0; l<i; l++) A[i][i] -= S[l][i]*S[l][i]*D[l];
                D[i] = (A[i][i]>=0) ? 1 : -1;
                S[i][i] = sqrt(D[i] * A[i][i]);
            }
            else {
                for (int l=0; l<j; l++) A[i][j] -= S[l][i]*S[l][j]*D[l];
                S[i][j] = A[i][j] / (S[i][i] * D[i]);
            }
        }
    }
    // S*Dy=b
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) b[i] -= S[j][i] * D[j] * b[j];
        b[i] /= S[i][i] * D[i];
    }
    // Sx = y
    for (int i = N - 1; i >= 0; i--) {
        for (int k = i + 1; k < N; k++) b[i] -= S[i][k] * x[k];
        x[i] = b[i] / S[i][i];
    }

    for (int i = 0; i < N; i++) delete[] S[i];
    delete[] S;
    delete[] D;
}



/**
 * Метод Якоби или Зейделя
 */
void gladyshevadn::lab5()
{
    double eps = 1e-10;
    double norm = 1;
    double* tempX = new double[N];
    for (int i=0; i<N; i++) x[i] = 0;
    while(norm>eps){
        norm = 0;
        for (int i=0; i<N; i++){
            tempX[i] = b[i];
            for (int j=0; j<N; j++) if (j!=i) tempX[i] -= A[i][j] * x[j];
            tempX[i] /= A[i][i];
            norm += fabs(tempX[i]-x[i]);
            x[i] = tempX[i];
        }
    }

    delete[]tempX;
}



/**
 * Метод минимальных невязок
 */
void gladyshevadn::lab6()
{
    double eps = 1e-9;
    double* r = new double[N];
    double* Ar = new double[N];
    for (int i=0; i<N; i++) x[i]=0;
    bool flag = true;
    while(flag){
        flag = false;
        // начальная невязка
        for (int i=0; i<N; i++){
            r[i] = b[i];
            for (int j=0; j<N; j++) r[i] -= A[i][j]*x[j];
        }
        // считаем A*r[k]
        for (int i=0; i<N; i++){
            Ar[i] = 0;
            for (int j=0; j<N; j++) Ar[i] += A[i][j] * r[j];
        }
        // считаем (A*r[k],r[k])
        double Arr = 0;
        for (int i=0; i<N; i++){
            Arr += Ar[i]*r[i];
        }
        // считаем норму Ar*Ar
        double norma_Ar = 0;
        for (int i=0; i<N; i++) norma_Ar += Ar[i] * Ar[i];
        // считаем тау
        double t = Arr / norma_Ar;
        // считаем икс и сравниваем разницу с заданной точностью
        for(int i=0; i<N; i++){
            double temp_x = x[i];
            x[i] += t * r[i];
            if (abs(temp_x - x[i]) > eps) flag = true;
        }
    }

    delete[]r;
    delete[]Ar;
}



/**
 * Метод сопряженных градиентов
 */
void gladyshevadn::lab7()
{

}


void gladyshevadn::lab8()
{

}


void gladyshevadn::lab9()
{

}


std::string gladyshevadn::get_name()
{
  return "Gladysheva D.N.";
}
