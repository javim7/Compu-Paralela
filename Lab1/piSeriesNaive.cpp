#include <stdio.h>

int main() {
    int n = 100000; // Número de términos en la serie

    double factor = 1.0;
    double sum = 0.0;

    for (int k = 0; k < n; k++) {
        sum += factor / (2 * k + 1);
        factor = -factor;
    }

    double pi_approx = 4.0 * sum;

    printf("Aproximación de pi: %lf\n", pi_approx);

    return 0;
}