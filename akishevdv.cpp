#include "akishevdv.h"

/**
 * Введение в дисциплину
 */
void akishevdv::lab1()
{
    cout << "Hello world!" << endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void akishevdv::lab2()
{
    int max;
    double sum = 0;
    //прямой ход
    for (int i = 0; i < N; i++)
    {
        max = i;
        double* help_one;
        double help_two;

        for (int j = i + 1; j < N; j++)
        {
            if (fabs(A[j][i]) > fabs(A[max][i]))
            {
                max = j;
            }
        }
        if (max != i)
        {
            help_one = A[i];
            A[i] = A[max];
            A[max] = help_one;

            help_two = b[i];
            b[i] = b[max];
            b[max] = help_two;
        }

        for (int j = N - 1; j > i; j--)
        {
            A[i][j] /= A[i][i];
        }
        b[i] /= A[i][i];
        A[i][i] = 1;

        for (int j = i + 1; j < N; j++)
        {
            for (int k = N - 1; k > i; k--)
            {
                A[j][k] = A[j][k] - A[j][i] * A[i][k];
            }
            b[j] = b[j] - A[j][i] * b[i];
            A[j][i] = 0;
        }
    }

    //обратный ход
    x[N - 1] = b[N - 1];
    for (int i = N - 2; i > -1; i--)
    {
        for (int j = i + 1; j < N; j++)
        {
            sum += x[j] * A[i][j];
        }
        x[i] = b[i] - sum;
        sum = 0;
    }

}


/**
 * Метод прогонки
 */
void akishevdv::lab3()
{
    double *alph = new double[N];
    double *bet = new double[N];

    alph[0] = -A[0][1] / A[0][0];
    bet[0] = b[0] / A[0][0];

    for (int i = 1; i < N - 1; i++) {
        alph[i] = -A[i][i + 1] / (A[i][i - 1] * alph[i - 1] + A[i][i]);
        bet[i] = (-A[i][i - 1] * bet[i - 1] + b[i]) / (A[i][i - 1] * alph[i - 1] + A[i][i]);
    }

    bet[N - 1] = (-A[N - 1][N - 2] * bet[N - 2] + b[N - 1]) / (A[N - 1][N - 2] * alph[N - 2] + A[N - 1][N - 1]);

    x[N - 1] = bet[N - 1];

    for (int i = N - 2; i >= 0; i--) {
        x[i] = bet[i] + alph[i] * x[i + 1];
    }
}

/**
 * Метод Холецкого
 */
void akishevdv::lab4()
{
    double *d = new double[N];
    double *arr_sum = new double[N];
    double *y = new double[N];

    double **s = new double*[N];
    for (int i = 0; i < N; i++)
        s[i] = new double[N];

    for (int i = 0; i < N; i++)
    {
        arr_sum[i] = A[i][i];
    }

    if (arr_sum[0] > 0)
        d[0] = 1;
    else
        d[0] = -1;

    s[0][0] = sqrt(fabs(arr_sum[0]));
    for (int j = 1; j < N; j++)
    {
        s[0][j] = A[0][j] / (d[0] * s[0][0]);
    }
    double help_num = 0;
    for (int i = 1; i < N; i++)
    {
        for (int k = 0; k < i; k++)
        {
            arr_sum[i] -= d[k] * pow(s[k][i], 2);
        }
        if (arr_sum[i] > 0)
        {
            d[i] = 1;
        }
        else
        {
            d[i] = -1;
        }
        s[i][i] = sqrt(fabs(arr_sum[i]));

        for (int j = i + 1; j < N; j++)
        {
            for (int k = 0; k < i; k++)
            {
                help_num += d[k] * s[k][i] * s[k][j];
            }

            s[i][j] = (A[i][j] - help_num) / (d[i] * s[i][i]);
            help_num = 0;
        }
    }

    //---------Нахождение корней--------
    y[0] = b[0] / s[0][0];
    for (int i = 1; i < N; i++)
    {
        for (int k = 0; k < i; k++)
        {
            help_num += s[k][i] * y[k];
        }
        y[i] = (b[i] - help_num) / s[i][i];
        help_num = 0;
    }
    x[N - 1] = y[N - 1] / (d[N - 1] * s[N - 1][N - 1]);
    for (int i = N - 2; i >= 0; i--)
    {
        for (int k = i + 1; k < N; k++)
        {
            help_num += s[i][k] * x[k];
        }
        x[i] = (y[i] - d[i] * help_num) / (d[i] * s[i][i]);
        help_num = 0;
    }

    delete[]d;
    delete[]arr_sum;
    delete[]y;
    delete[]s;
}


/**
 * Метод Якоби или Зейделя
 */
void akishevdv::lab5()
{
    double eps = 1e-9;

    double* previous_result = new double[N];

    while (1) {
        for (int i = 0; i < N; i++)
            previous_result[i] = x[i];

        for (int i = 0; i < N; i++) {
            double sum = 0;

            for (int j = 0; j < i; j++){
                sum += A[i][j] * x[j];
            }

            for (int j = i + 1; j < N; j++){
                sum += A[i][j] * previous_result[j];
            }

            x[i] = (b[i] - sum) / A[i][i];
        }

        double difference = abs(x[0] - previous_result[0]);
        for (int i = 1; i < N; i++)
            if (abs(x[i] - previous_result[i]) > difference)
                difference = abs(x[i] - previous_result[i]);

        if (difference < eps)
            break;
    }

    delete[] previous_result;

}



/**
 * Метод минимальных невязок
 */
void akishevdv::lab6()
{
    double* functionality = new double[N];
    double* residual_vector = new double[N];

    double in_num, difference,
        tmp, tmp_two, help_one, help_two;

    while(1){
        for (int i = 0; i < N; i++) {
            tmp = 0;
            for (int j = 0; j < N; j++) {
                tmp += A[i][j] * x[j];
            }
            residual_vector[i] = tmp - b[i];
            functionality[i] = 2 * residual_vector[i];
        }
        double* array = new double[N];
        for (int i = 0; i < N; i++) {
            tmp_two = 0;
            for (int j = 0; j < N; j++) {
                tmp_two += A[i][j] * residual_vector[j];
            }
            array[i] = tmp_two;
        }

        help_one = 0;
        help_two = 0;
        for (int i = 0; i < N; i++) {
            help_one += abs(array[i] * residual_vector[i]);
            help_two += abs(array[i] * array[i]);
        }
        in_num = help_one / (2 * help_two);

        double*y = new double[N];
        for (int i = 0; i < N; i++) {
            y[i] = x[i];
        }
        for (int i = 0; i < N; i++) {
            x[i] = x[i] - in_num * functionality[i];
        }

        difference = 0;
        for (int i = 0; i < N; i++) {
            difference += (y[i] - x[i]) * (y[i] - x[i]);
        }
        if(!(sqrt(difference) > 1e-19)) break;
    }

}



/**
 * Метод сопряженных градиентов
 */
void akishevdv::lab7()
{
    double* residual_vector = new double[N];

    double norma;
    for(int i = 0; i < N; i++)
        norma += b[i] * b[i];

    double* r = new double[N];
    for (int i = 0; i < N; i++){
        double tmp = 0;
        for(int j = 0; j < N; j++){
            tmp += A[i][j] * x[j];
        }
        residual_vector[i] = b[i] - tmp;
        r[i] = residual_vector[i];
    }

    double* Ar = new double[N];
    for (int i = 0; i < N; i++){
        double tmp = 0;
        for(int j = 0; j < N; j++){
            tmp += A[i][j] * r[j];
        }
        Ar[i] = tmp;
    }

    double t1 = 0, t2 = 0;
    for (int i = 0; i < N; i++){
        t1 += residual_vector[i] * residual_vector[i];
        t2 += Ar[i] * r[i];
    }
    double alf = t1 / t2;

    double* residual_vector_help = new double[N];
    for(int i=0; i < N; i++){
        residual_vector_help[i] = residual_vector[i];
    }

    for(int i=0; i < N; i++){
        x[i] = x[i] + alf * r[i];
        residual_vector[i] = residual_vector[i] - alf * Ar[i];
    }

    for (int i = 0; i < N; i++){
        t1 += residual_vector[i] * residual_vector[i];
        t2 += residual_vector_help[i] * residual_vector_help[i];
    }
    double bet = t1 / t2;

    for(int i = 0; i < N; i++){
        r[i] = residual_vector[i] + bet * r[i];
    }

    double tr = 0;
    for(int i = 0; i < N; i++){
        tr += residual_vector[i] * residual_vector[i];
    }

    while(1){
        for (int i = 0; i < N; i++){
            double tmp = 0;
            for(int j = 0; j < N; j++){
                tmp += A[i][j] * r[j];
            }
            Ar[i] = tmp;
        }

        double ts1 = 0, ts2 = 0;
        for (int i = 0; i < N; i++){
            ts1 += residual_vector[i] * residual_vector[i];
            ts2 += Ar[i] * r[i];
        }
        alf = ts1/ts2;

        for(int i=0; i < N; i++){
            residual_vector_help[i] = residual_vector[i];
        }

        for(int i = 0; i < N; i++){
            x[i] = x[i] + alf * r[i];
            residual_vector[i] = residual_vector[i] - alf * Ar[i];
        }

        for (int i = 0; i < N; i++){
            ts1 += residual_vector[i] * residual_vector[i];
            ts2 += residual_vector_help[i] * residual_vector_help[i];
        }
        bet = ts1/ts2;

        for(int i = 0; i < N; i++){
            r[i] = residual_vector[i] + bet * r[i];
        }
        double tr = 0;
        for(int i = 0; i < N; i++){
            tr += residual_vector[i] * residual_vector[i];
        }
        if(!(sqrt(tr / norma) > 1e-21)) break;
    }

    delete[] residual_vector;
    delete[] residual_vector_help;
    delete[] Ar;
    delete[] r;
}


void akishevdv::lab8()
{
    double error = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (i != j)
                error += A[i][j] * A[i][j];
    //-----------------
    int ii = 0;
    int jj = 1;
    double max_elem = A[0][1];
    while (sqrt(error) > 1)
    {
        for (int i = 0; i < N; i++)
            for (int j = i + 1; j < N; j++)
                if (abs(A[i][j]) >= abs(max_elem))
                {
                    max_elem = A[i][j];
                    ii = i;
                    jj = j;
                }
        //------------------------
        double alpha;
        if (A[ii][ii] == A[jj][jj])
            alpha = M_PI / 4;
        else alpha = atan((2 * A[ii][jj]) / (A[jj][jj] - A[ii][ii])) / 2;

        double c = cos(alpha);
        double s = sin(alpha);

        double **C = new double*[N];
        for (int i = 0; i < N; i++)
            C[i] = new double[N];

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                C[i][j] = 0;

        C[ii][ii] = pow(c, 2) * A[ii][ii] - 2*s*c * A[ii][jj] + pow(s, 2) * A[jj][jj];
        C[jj][jj] = pow(s, 2) * A[ii][ii] + 2*s*c * A[ii][jj] + pow(c, 2) * A[jj][jj];
        C[ii][jj] = (pow(c, 2) - pow(s, 2)) * A[ii][jj] + s * c * (A[ii][ii] - A[jj][jj]);
        C[jj][ii] = C[ii][jj];
        for (int k = 0; k < N; k++)
            if (k != ii && k != jj)
            {
                C[ii][k] = c * A[ii][k] - s * A[jj][k];
                C[k][ii] = C[ii][k];
            }

        for (int k = 0; k < N; k++)
            if (k != ii && k != jj)
            {
                C[jj][k] = s * A[ii][k] + c * A[jj][k];
                C[k][jj] = C[jj][k];
            }

        for (int k = 0; k < N; k++)
            for (int l = 0; l < N; l++)
                if (k != ii && k != jj && l != ii && l != jj)
                    C[k][l] = A[k][l];

        error = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (i != j)
                    error += C[i][j] * C[i][j];

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                A[i][j] = C[i][j];

        max_elem = A[0][1];
        delete[] C;
    }

    for (int i = 0; i < N; i++)
        x[i] = A[i][i];
}


void akishevdv::lab9()
{

}


std::string akishevdv::get_name()
{
  return "Akishev D.V.";
}
