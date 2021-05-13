#include "kulaginpa.h"

/**
 * Введение в дисциплину
 */
void kulaginpa::lab1()
{
	std::cout << "Hello world!!!!!" << std::endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void kulaginpa::lab2()
{
	size_t n = N;

	for (size_t i = 0; i < n; i++) // прямой ход
	{
		size_t main_element_pos = i;
		for (size_t j = i; j < n; j++) // поиск главного элемента, начиная с i-ой строки
		{
			if (A[main_element_pos][i] < A[j][i])
				main_element_pos = j;
		}
		double tmp_element;
		if (main_element_pos != i) // если главный элемент не находится на диагонали
		{
			for (size_t j = i; j < n; j++) // меняем строки местами
			{
				tmp_element = A[i][j];
				A[i][j] = A[main_element_pos][j];
				A[main_element_pos][j] = tmp_element;
			}
			tmp_element = b[i];
			b[i] = b[main_element_pos];
			b[main_element_pos] = tmp_element;
		}
		for (size_t j = i + 1; j < n; j++)
		{
			double c = A[j][i] / A[i][i];
			for (size_t k = i; k < n; k++)
			{
				A[j][k] -= c * A[i][k];
			}
			b[j] -= c * b[i];
		}
	}

	for (int i = N - 1; i >= 0; i--) // обратный ход
	{
		for (int j = i - 1; j >= 0; j--)
		{
			double c = A[j][i] / A[i][i];
			for (int k = i; k >= 0; k--)
			{
				A[j][k] -= c * A[i][k];
			}
			b[j] -= c * b[i];
		}
	}

	for (size_t i = 0; i < n; i++) 
	{
		x[i] = b[i] / A[i][i];
	}
}



/**
 * Метод прогонки
 */
void kulaginpa::lab3()
{
	size_t n = N;
	double * alpha = new double[N];
	double * beta = new double[N];

	double y = A[0][0];
	alpha[0] = -A[0][1] / y;
	beta[0] = b[0] / y;

	for (size_t i = 1; i < n - 1; i++) // прямой ход
	{
		y = A[i][i] + A[i][i - 1] * alpha[i - 1];
		alpha[i] = -A[i][i + 1] / y;
		beta[i] = (b[i] - A[i][i - 1] * beta[i - 1]) / y;
	}
	y = A[n - 1][n - 1] + A[n - 1][n - 2] * alpha[n - 2];
	beta[n - 1] = (b[n - 1] - A[n - 1][n - 2] * beta[n - 2]) / y;

	x[n - 1] = beta[n - 1];
	for (int i = N - 2; i >= 0; i--) 
	{
		x[i] = alpha[i] * x[i + 1] + beta[i];
	}

	delete[] alpha;
	delete[] beta;
}



/**
 * Метод Холецкого
 */
void kulaginpa::lab4()
{
	size_t n = N;
	double * D = new double[N];
	double **S = new double*[N];
	S[0] = new double[N * N];
	for (size_t i = 0; i < n; i++)
	{
		S[i] = S[0] + i * N;
	}

	for (size_t i = 0; i < n; i++)
	{
		double tmp = A[i][i];
		for (size_t k = 0; k < i; k++)
		{
			tmp -= S[k][i] * S[k][i] * D[k];
		}
		D[i] = tmp > 0 ? 1 : -1;
		S[i][i] = sqrt(tmp * D[i]);
		for (size_t j = i + 1; j < n; j++)
		{
			double tmp2 = A[i][j];
			for (size_t k = 0; k < i; k++)
			{
				tmp2 -= S[k][i] * D[k] * S[k][j];
			}
			S[i][j] = tmp2 / (S[i][i] * D[i]);
		}
	}

	for (size_t i = 0; i < n; i++) 
	{
		for (size_t j = 0; j < i; j++) 
		{
			b[i] -= S[j][i] * D[j] * b[j];
		}
		b[i] /= S[i][i] * D[i];
	}

	
	for (int i = N - 1; i >= 0; i--) 
	{
		for (size_t k = i + 1; k < n; k++) 
		{
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
void kulaginpa::lab5()
{
	size_t n = N;
	double eps = 1.E-10;
	for (size_t i = 0; i < n; i++)
		x[i] = A[i][i];

	bool stop = false;
	double *next_x_arr = new double[N];

	while (!stop)
	{
		for (size_t i = 0; i < n; i++)
		{
			double temp_x = b[i];
			for (size_t j = 0; j < n; j++)
			{
				if (i == j) 
					continue;
				temp_x -= x[j] * A[i][j];
			}
			next_x_arr[i] = temp_x / A[i][i];
		}
		stop = true;
		for (size_t i = 0; i < n; i++)
		{
			if (abs(x[i] - next_x_arr[i]) > eps)
				stop = false;
			x[i] = next_x_arr[i];
		}
	}

	delete[] next_x_arr;
}



/**
 * Метод минимальных невязок
 */
void kulaginpa::lab6()
{
	size_t n = N;
	double eps = 1.E-10;
	double *r = new double[N];
	double *Ar = new double[N];
	bool stop = false;

	//начальное приближение
	for (size_t i = 0; i < n; i++)
		x[i] = A[i][i];
	

	while (!stop)
	{
		// вычисление невязки (1)
		for (size_t i = 0; i < n; i++)
		{
			r[i] = b[i];
			for (size_t j = 0; j < n; j++)
				r[i] -= A[i][j] * x[j];
		}
		// вычисление произведения A * r
		for (size_t i = 0; i < n; i++)
		{
			Ar[i] = 0;
			for (size_t j = 0; j < n; j++)
				Ar[i] += A[i][j] * r[j];
		}
		// вычисление скалярных произведений для тау
		double scal_mult_Ar_r = 0;
		double scal_mult_Ar_Ar = 0;
		for (size_t i = 0; i < n; i++)
		{
			scal_mult_Ar_r += Ar[i] * r[i];
			scal_mult_Ar_Ar += Ar[i] * Ar[i];
		}
		double tau = scal_mult_Ar_r / scal_mult_Ar_Ar;
		// вычисление нового значения x, зная тау (2)
		stop = true;
		for (size_t i = 0; i < n; i++) 
		{
			double new_x = x[i] + tau * r[i];
			if (abs(x[i] - new_x) > eps)
				stop = false;
			x[i] = new_x;
		}
	}
	delete[] r;
	delete[] Ar;
}



/**
 * Метод сопряженных градиентов
 */
void kulaginpa::lab7()
{
	size_t n = N;
	double eps = 1.E-10;
	double *r = new double[N];
	double *Ar = new double[N];
	double **E = new double*[N];
	E[0] = new double[N*N];
	for (int i = 0; i < N; i++)
		E[i] = E[0] + i * N;

	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n; j++)
			i != j ? E[i][j] = 0 : E[i][j] = 1;

	//начальное приближаение
	for (size_t i = 0; i < n; i++)
		x[i] = A[i][i];
	// вычисление невязки (1)
	for (size_t i = 0; i < n; i++)
	{
		r[i] = b[i];
		for (size_t j = 0; j < n; j++)
			r[i] -= A[i][j] * x[j];
	}
	double scalar_mult_r_r = 0;
	for (size_t i = 0; i < n; i++)
		scalar_mult_r_r += r[i] * r[i];

	// вычисление произведения A * r
	for (size_t i = 0; i < n; i++)
	{
		Ar[i] = 0;
		for (size_t j = 0; j < n; j++)
			Ar[i] += A[i][j] * r[j];
	}
	double scalar_mult_Ar_r = 0;
	for (size_t i = 0; i < n; i++)
		scalar_mult_Ar_r += Ar[i] * r[i];

	double tau = scalar_mult_r_r / scalar_mult_Ar_r;
	
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++)
			E[i][j] -= tau * A[i][j];
	}

	double *tau_b = new double[N];
	double *E_x = new double[N];
	for (size_t i = 0; i < n; i++)
	{
		tau_b[i] = tau * b[i];
		E_x[i] = 0;
		for (size_t j = 0; j < n; j++)
			E_x[i] += E[i][j] * x[j];
	}

	for (size_t i = 0; i < n; i++)
		x[i] = E_x[i] + tau_b[i];

	bool stop = false;
	double scalar_mult_r_r_prev = scalar_mult_r_r;
	double alpha, alpha_prev = 1;
	double tau_prev = tau;
	while (!stop)
	{
		// Вычисление (r,r)
		for (size_t i = 0; i < n; i++)
		{
			r[i] = b[i];
			for (size_t j = 0; j < n; j++)
				r[i] -= A[i][j] * x[j];
		}
		for (size_t i = 0; i < n; i++)
			scalar_mult_r_r += r[i] * r[i];

		// вычисление (Ar,r)
		for (size_t i = 0; i < n; i++)
		{
			Ar[i] = 0;
			for (size_t j = 0; j < n; j++)
				Ar[i] += A[i][j] * r[j];
		}
		double scalar_mult_Ar_r = 0;
		for (size_t i = 0; i < n; i++)
			scalar_mult_Ar_r += Ar[i] * r[i];
		
		tau = scalar_mult_r_r / scalar_mult_Ar_r;

		alpha = 1. / (1 - (1. / alpha_prev) * (tau / tau_prev) * (scalar_mult_r_r / scalar_mult_r_r_prev));

		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < n; j++)
				i != j ? E[i][j] = 0 : E[i][j] = 1;

		for (size_t i = 0; i < n; i++) 
			for (size_t j = 0; j < n; j++) 
				E[i][j] -= tau * A[i][j];

		for (size_t i = 0; i < n; i++)
		{
			tau_b[i] = alpha * tau * b[i];
			E_x[i] = 0;
			for (size_t j = 0; j < n; j++)
				E_x[i] += E[i][j] * x[j];
			E_x[i] *= alpha;
		}

		stop = true;
		for (size_t i = 0; i < n; i++)
		{
			double new_x = E_x[i] + (1 - alpha) * x[i] + tau_b[i];
			if (abs(x[i] - new_x) > eps)
				stop = false;
			x[i] = new_x;
		}

		alpha_prev = alpha;
		tau_prev = tau;
		scalar_mult_r_r_prev = scalar_mult_r_r;		
	}
	delete[] r;
	delete[] Ar;
	delete[] E[0];
	delete[] E;
	delete[] tau_b;
	delete[] E_x;
}


void kulaginpa::lab8()
{

}


void kulaginpa::lab9()
{

}


std::string kulaginpa::get_name()
{
  return "Kulagin P.A.";
}
