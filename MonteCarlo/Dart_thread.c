#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

long long monte_carlo(long long);

int main(int argc, char *argv[])
{
    long long iterations = atoll(argv[1]);
    double pi;
    long long circle = 0;
    srand(time(NULL));
    clock_t start = clock();
    circle = monte_carlo(iterations);
    pi = 4.0 * circle / (double)iterations;
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Pi: %f\n", pi);
    printf("La ejecucion ha tomado %.4f segundos\n", seconds);
    return 0;
}

long long monte_carlo(long long iterations)
{
    double x, y, d;
    long long circle = 0;

    for (long long i = 0; i < iterations; i++)
    {
        x = ((double)rand() / (double)(RAND_MAX / 2) - 1);
        y = ((double)rand() / (double)(RAND_MAX / 2)) - 1;
        d = (x * x) + (y * y);
        if (d <= 1)
            circle++;
    }
    return circle;
}