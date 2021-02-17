#include "zavaryuhinayuv.h"

/**
 * Введение в дисциплину
 */
void zavaryuhinayuv::lab1()
{
    cout << "hello world!!!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void zavaryuhinayuv::lab2()
{
    int i,j, mxi,k;
    double c;
    for (i=0; i<N; i++){
        mxi=i;
        double maxi = A[i][i];
        for (j=i+1; j<N; j++){
            if (abs(A[j][i]) > maxi)
            {
                maxi = abs(A[j][i]); mxi=j;
            }
        }
        swap(A[i],A[mxi]);
        swap(b[i],b[mxi]);
        for (j=i+1; j<N; j++){
            c = A[j][i]/A[i][i];
            for (k=i+1; k<N; k++){
                A[j][k]=A[j][k]-c*A[i][k];
            }
            b[j]=b[j]-c*b[i];
            A[j][i] = 0;

        }

    }
    for (i=0; i<N; i++){
        c=A[i][i];
        for (j=i+1; j<N; j++){
            A[i][j]=A[i][j]/c;
        }
        A[i][i]=1;
        b[i]=b[i]/c;
    }
    for (i=N-1; i>=0; i--){
        for (j=i-1; j>=0; j--){
            c=A[j][i];
            b[j]=b[j]-c*b[i];
            A[j][i]=0;
        }


    }
    for (i=0; i<N; i++){
        x[i]=b[i];
    }
}



/**
 * Метод прогонки
 */
void zavaryuhinayuv::lab3()
{

}



/**
 * Метод Холецкого
 */
void zavaryuhinayuv::lab4()
{

}



/**
 * Метод Якоби или Зейделя
 */
void zavaryuhinayuv::lab5()
{

}



/**
 * Метод минимальных невязок
 */
void zavaryuhinayuv::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void zavaryuhinayuv::lab7()
{

}


void zavaryuhinayuv::lab8()
{

}


void zavaryuhinayuv::lab9()
{

}


std::string zavaryuhinayuv::get_name()
{
    return "Zavaryukhina Y.V.";
}
