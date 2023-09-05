#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int thread_count = 2000; // Número de hilos por defecto

    if (argc > 1)
    {
        thread_count = atoi(argv[1]);
    }
    else
    {
        printf("Número de hilos no especificado. Usando valor por defecto: 2000.\n");
    }

    int n = 1000000000; // Número de términos en la serie

    long double sum = 0.0;
    long double factor;

#pragma omp parallel for num_threads(thread_count) \
    reduction(+ : sum) private(factor)
    for (int k = 0; k < n; k++)
    {
        factor = (k % 2 == 0) ? 1.0 : -1.0;
        sum += factor / (2 * k + 1);
    }

    long double pi_approx = 4.0 * sum;

    printf("Aproximación de pi: %.*Lf\n", 20, pi_approx);

    return 0;
}
