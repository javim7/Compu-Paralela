#include <stdio.h>
#include <omp.h>

int main()
{
    int thread_count = 1; // Número de hilos a utilizar
    int n = 1000000;      // Número de términos en la serie

    double sum = 0.0;

#pragma omp parallel for num_threads(thread_count) \
    reduction(+ : sum)
    for (int k = 0; k < n; k++)
    {
        double factor = (k % 2 == 0) ? 1.0 : -1.0;
        sum += factor / (2 * k + 1);
    }

    double pi_approx = 4.0 * sum;

    printf("Aproximación de pi: %.*lf\n", 18, pi_approx);

    return 0;
}
