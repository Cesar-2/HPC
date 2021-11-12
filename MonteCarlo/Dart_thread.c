#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

int monte_carlo();

#ifndef MPI
#define M_PI 3.14159265358979323846
#endif
long long n_crossed = 0;
long long iterations;
int num_of_threads;
int count;
double l;

int main(int argc, char *argv[])
{
    long rank;
    double l = atof(argv[1]);
    long long iterations = atoll(argv[2]);
    int thread = atoi(argv[3]);
    pthread_t tid[thread];
    double p, pi;
    long long n_crossed;
    srand(time(NULL));
    clock_t start = clock();
    for (rank = 0; rank < num_of_threads; rank++)
        pthread_create(&tid[rank], NULL, monte_carlo, (void *)rank);
    for (rank = 0; rank < num_of_threads; rank++)
        pthread_join(tid[rank], NULL);
    p = n_crossed / (double)iterations;
    pi = 2.0 / (p * l);
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("La probabilidad es de: %f\n", p);
    printf("Pi: %f\n", pi);
    printf("El tiempo de ejecucion fue de %.4f segundos\n", seconds);
    return 0;
}

int monte_carlo()
{
    double x, theta, n;
    for (long long i = 0; i < iterations; i++)
    {
        x = (double)rand() / (double)(RAND_MAX / l);
        theta = (double)rand() / (double)(RAND_MAX / M_PI);

        n = sin(theta) / 2.0;
        if (x + n >= l || x - n <= 0)
            n_crossed++;
    }
}