#include "potapkinayuyu.h"

/**
 * Введение в дисциплину
 */
void potapkinayuyu::lab1()
{
  cout << "Hello World!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */


void potapkinayuyu::lab2()
{
	double maxi;
	int k, u;
	double eps = 0.000001;

	k = 0;
	while (k < N)
	{
		maxi = abs(A[k][k]);
		u = k;
		for (int i = k + 1; i < N; i++) {
			if (abs(A[i][k]) > maxi) {
				maxi = abs(A[i][k]);
				u = i;
			}
		}

		for (int j = 0; j < N; j++) {
			swap(A[k][j], A[u][j]);
		}

		swap(b[k], b[u]);
		for (int i = k; i < N; i++) {
			double c = A[i][k];
			if (abs(c) < eps) continue;
			for (int j = 0; j < N; j++) {
				A[i][j] = A[i][j] / c;
			}

			b[i] = b[i] / c;
			if (i == k)	continue;
			for (int j = 0; j < N; j++) {
				A[i][j] = A[i][j] - A[k][j];
			}

			b[i] = b[i] - b[k];
		}

		k++;
	}

	for (k = N - 1; k >= 0; k--) {
		x[k] = b[k];
		for (int i = k - 1; i >= 0; i--) {
			double c = A[i][k];
			for (int j = 0; j < N; j++) {
				A[i][j] = A[k][j] * c + A[i][j];
			}
			b[i] = -b[k] * c + b[i];
		}
	}
}



/**
 * Метод прогонки
 */
void potapkinayuyu::lab3()
{
	double* P = new double[N];
	double* Q = new double[N];

	for (int i = 0; i < N; i++) {
		P[i] = 0;
		Q[i] = 0;
	}

	P[0] = (-A[0][1]) / A[0][0];
	Q[0] = b[0] / A[0][0];

	for (int i = 1; i < N; i++) {
		P[i] = A[i][i + 1] / (-A[i][i] - A[i][i - 1] * P[i - 1]);
		Q[i] = (-b[i] + A[i][i - 1] * Q[i - 1]) / (-A[i][i] - A[i][i - 1] * P[i - 1]);
	}

	x[N - 1] = Q[N - 1];
	for (int i = N - 2; i >= 0; i--) {
		x[i] = P[i] * x[i + 1] + Q[i];
	}

	delete[] P;
	delete[] Q;
}



/**
 * Метод Холецкого
 */
void potapkinayuyu::lab4()
{


	double* D = new double[N];
	double** S = new double* [N];
	S[0] = new double[N * N];

	for (int i = 0; i < N; i++) {
		S[i] = S[0] + i * N;
	}

	for (int i = 0; i < N; i++) {
		double c = A[i][i];
		for (int k = 0; k < i; k++) {
			c -= S[k][i] * S[k][i] * D[k];
		}
		D[i] = c > 0 ? 1 : -1;
		S[i][i] = sqrt(c * D[i]);
		for (int j = i + 1; j < N; j++) {
			double c2 = A[i][j];
			for (int k = 0; k < i; k++) {
				c2 -= S[k][i] * D[k] * S[k][j];
			}
			S[i][j] = c2 / (S[i][i] * D[i]);
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i; j++) {
			b[i] -= S[j][i] * D[j] * b[j];
		}
		b[i] /= S[i][i] * D[i];
	}


	for (int i = N - 1; i >= 0; i--) {
		for (int k = i + 1; k < N; k++) {
			b[i] -= S[i][k] * x[k];
		}
		x[i] = b[i] / S[i][i];
	}

	delete[] S[0];
	delete[] S;
	delete[] D;
}






/**
 * Метод Якоби или Зейделя
 */
void potapkinayuyu::lab5()
{

}



/**
 * Метод минимальных невязок
 */
void potapkinayuyu::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void potapkinayuyu::lab7()
{

}


void potapkinayuyu::lab8()
{

}


void potapkinayuyu::lab9()
{

}


std::string potapkinayuyu::get_name()
{
  return "Potapkina Yu.Yu.";
}
