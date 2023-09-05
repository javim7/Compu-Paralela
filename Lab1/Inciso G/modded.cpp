#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

long double compute_pi(int n, int thread_count)
{
    long double sum = 0.0;
    long double factor;

#pragma omp parallel for num_threads(thread_count) reduction(+ : sum) private(factor)
    for (int k = 0; k < n; k++)
    {
        factor = (k % 2 == 0) ? 1.0 : -1.0;
        sum += factor / (2 * k + 1);
    }

    return 4.0 * sum;
}

void measure_and_print(omp_sched_t schedule_type, const char *schedule_name, int n, int thread_count, int block_size)
{
    const int iterations = 5;
    double total_time = 0.0;

    if (block_size != -1)
    { // block_size = -1 for auto schedule
        omp_set_schedule(schedule_type, block_size);
    }

    for (int i = 0; i < iterations; i++)
    {
        double start_time = omp_get_wtime();
        long double pi = compute_pi(n, thread_count);
        double end_time = omp_get_wtime();
        double elapsed = end_time - start_time;
        total_time += elapsed;

        printf("%s with block_size %d (Iteración %d): %f segundos, Aproximación de pi: %.*Lf\n", schedule_name, block_size, i + 1, elapsed, 20, pi);
    }

    printf("Promedio para %s with block_size %d: %f segundos\n\n", schedule_name, block_size, total_time / iterations);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Uso: %s <cores> <n>\n", argv[0]);
        return 1;
    }

    int cores = atoi(argv[1]);
    int n = atoi(argv[2]);

    // Si los valores proporcionados son inválidos, utilice los valores por defecto.
    if (cores <= 0)
    {
        cores = omp_get_max_threads();
        printf("Número de cores no especificado o inválido. Usando valor por defecto: %d.\n", cores);
    }

    if (n <= 0)
    {
        n = 1e6;
        printf("Valor de 'n' no especificado o inválido. Usando valor por defecto: %d.\n", n);
    }

    omp_sched_t schedules[] = {omp_sched_static, omp_sched_dynamic, omp_sched_guided, omp_sched_auto};
    const char *schedule_names[] = {"static", "dynamic", "guided", "auto"};
    int block_sizes[] = {16, 64, 128};

    for (int i = 0; i < 4; i++)
    {
        if (schedules[i] == omp_sched_auto)
        {
            measure_and_print(schedules[i], schedule_names[i], n, cores, -1); // -1 as block_size for auto schedule
        }
        else
        {
            for (int j = 0; j < 3; j++)
            {
                measure_and_print(schedules[i], schedule_names[i], n, cores, block_sizes[j]);
            }
        }
    }

    return 0;
}
