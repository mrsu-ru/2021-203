﻿#include "zavaryuhinayuv.h"

/**
 * Введение в дисциплину
 */
void zavaryuhinayuv::lab1() {
    cout << "hello world!!!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void zavaryuhinayuv::lab2() {
    int i, j, mxi, k;
    double c;
    for (i = 0; i < N; i++) {
        mxi = i;
        double maxi = A[i][i];
        for (j = i + 1; j < N; j++) {
            if (abs(A[j][i]) > maxi) {
                maxi = abs(A[j][i]);
                mxi = j;
            }
        }
        swap(A[i], A[mxi]);
        swap(b[i], b[mxi]);
        for (j = i + 1; j < N; j++) {
            c = A[j][i] / A[i][i];
            for (k = i + 1; k < N; k++) {
                A[j][k] = A[j][k] - c * A[i][k];
            }
            b[j] = b[j] - c * b[i];
            A[j][i] = 0;

        }

    }
    for (i = 0; i < N; i++) {
        c = A[i][i];
        for (j = i + 1; j < N; j++) {
            A[i][j] = A[i][j] / c;
        }
        A[i][i] = 1;
        b[i] = b[i] / c;
    }
    for (i = N - 1; i >= 0; i--) {
        for (j = i - 1; j >= 0; j--) {
            c = A[j][i];
            b[j] = b[j] - c * b[i];
            A[j][i] = 0;
        }


    }
    for (i = 0; i < N; i++) {
        x[i] = b[i];
    }
}


/**
 * Метод прогонки
 */
void zavaryuhinayuv::lab3() {
    int i;
    double alp[N];
    double bet[N];

    alp[0] = -A[0][1] / A[0][0];
    bet[0] = b[0] / A[0][0];
    for (i = 1; i < N; i++) {
        alp[i] = -A[i][i + 1] / (A[i][i] + A[i][i - 1] * alp[i - 1]);
        bet[i] = (b[i] - A[i][i - 1] * bet[i - 1]) / (A[i][i] + A[i][i - 1] * alp[i - 1]);
    }
    x[N - 1] = bet[N - 1];
    for (i = N - 2; i > -1; i--) {
        x[i] = bet[i] + alp[i] * x[i + 1];
    }

}


/**
 * Метод Холецкого
 */
void zavaryuhinayuv::lab4() {
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
void zavaryuhinayuv::lab5() {
    //Зейделя
    int i, j;
    for (i = 0; i < N; i++) {
        x[i] = 1;
    }
    double *x2 = new double[N];
    bool temp = true;
    while (temp) {
        temp = false;
        for (i = 0; i < N; i++) {
            x2[i] = b[i];
            for (j = 0; j < N; j++) {
                if (i == j) continue;
                x2[i] = x2[i] + x[j] * (-A[i][j]);
            }
            x2[i] = x2[i] / A[i][i];

            if (fabs(x2[i] - x[i]) > 1e-9) {
                temp = true;
            }

            x[i] = x2[i];

        }
    }
    delete[] x2;
}


/**
 * Метод минимальных невязок
 */
void zavaryuhinayuv::lab6() {

    double *r = new double[N];
    double *ar= new double[N];
    double t=0;
    double ar2=0;

    bool temp = true;

    while(temp){
        temp=false;

        for (int i=0; i<N; i++){
            r[i]=b[i];
             for (int j=0; j<N; j++){
                 r[i]=r[i]-A[i][j]*x[j];

             }
        }
        for (int i=0; i<N; i++){
            ar[i]=0;
            for (int j=0; j<N; j++){
                ar[i]=ar[i]+A[i][j]*r[j];

            }
        }
        double t=0;
        double ar2=0;

        for (int i=0; i<N; i++){
            t=t+ar[i]*r[i];
            ar2=ar2+ar[i]*ar[i];
        }

        t= t/ar2;

        for (int i=0; i<N; i++){
            double temp_x=x[i];
            x[i]=x[i]+t*r[i];
            if (fabs(x[i]-temp_x)>1.e-9){ temp=true;}
        }


    }

    delete[] r;
    delete[] ar;



}


/**
 * Метод сопряженных градиентов
 */
void zavaryuhinayuv::lab7() {
    double *r= new double[N];
    double *ar = new double[N];
    double *kx= new double[N];
    double r_sc=0;
    double ar_sc=0;
    double t;
    double a=1;
    bool temp=true;

    for (int i = 0; i < N; i++) {
        x[i] = 0;
        r[i] = -b[i];
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            r[i] = r[i] + A[i][j] * x[j];
        }
    }

    for (int i = 0; i < N; i++) {
        ar[i] = 0;
        for (int j = 0; j < N; j++) {
            ar[i]= ar[i]+ A[i][j] * r[j];
        }
        }
    for (int i = 0; i < N; i++) {
        r_sc += r[i] * r[i];
        ar_sc += ar[i] * r[i];
    }
     t=r_sc/ar_sc;
    for (int i = 0; i < N; i++) {
        x[i] = t * b[i];
    }

    while (temp) {
        temp = false;
        for (int i = 0; i < N; i++) {
            r[i] = -b[i];
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                r[i] = r[i] + A[i][j] * x[j];
            }
        }
        for (int i = 0; i < N; i++) {
            ar[i] = 0;
            for (int j = 0; j < N; j++) {
                ar[i] = ar[i] + A[i][j] * r[j];
            }
        }
        double t_t = t;
        double t_sc = ar_sc;
        r_sc = 0;
        ar_sc = 0;
        for (int i = 0; i < N; i++) {
            r_sc = r_sc + r[i] * r[i];
            ar_sc = ar_sc + ar[i] * r[i];
        }
        t = r_sc / ar_sc;
        a = 1.0 / (1 - (t * r_sc) / (a * t_t * t_sc));
        for (int i = 0; i < N; i++) {
            double t_x = x[i];
            x[i] = a * x[i] + (1 - a) * kx[i] - t * a * r[i];
            kx[i] = t_x;
            if (fabs(x[i] - t_x) > 1e-9) temp = true;
        }
    }

    delete[] r;
    delete[] ar;
    delete kx;

}



void zavaryuhinayuv::lab8() {

}


void zavaryuhinayuv::lab9() {

}


std::string zavaryuhinayuv::get_name() {
    return "Zavaryukhina Y.V.";
}
