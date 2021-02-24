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

}



/**
 * Метод Холецкого
 */
void kulaginpa::lab4()
{

}



/**
 * Метод Якоби или Зейделя
 */
void kulaginpa::lab5()
{

}



/**
 * Метод минимальных невязок
 */
void kulaginpa::lab6()
{

}



/**
 * Метод сопряженных градиентов
 */
void kulaginpa::lab7()
{

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
