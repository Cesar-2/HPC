#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <error.h>
#include <pthread.h>

#ifndef MPI
#define M_PI 3.14159265358979323846
#endif
#define MAX_THREADS 8

pthread_mutex_t mutex;
long long add = 0;
typedef struct
{
    long long iterations;
    long long total_iterations;
    double l;
    int thread;
} structure_data;

void monte_carlo(structure_data *, pthread_t *, double, long long);
void *needles(void *structure_data);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    double l = atof(argv[1]);
    long long iterations = atoll(argv[2]);
    double p, pi;
    structure_data *data = NULL;
    pthread_t *threads = (pthread_t *)malloc(MAX_THREADS * sizeof(pthread_t));
    clock_t start = clock();
    monte_carlo(data, threads, l, iterations);
    p = add / (double)iterations;
    pi = 2.0 / (p * l);
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Probabilidad: %f\nPi: %f\nTiempo de ejecucion fue %.4f segundos\n", p, pi, seconds);
    return 0;
}

void monte_carlo(structure_data *data, pthread_t *threads, double l, long long iterations)
{

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < MAX_THREADS; i++)
    {
        data = (structure_data *)malloc(sizeof(structure_data));
        data->iterations = iterations / MAX_THREADS;
        data->total_iterations = iterations;
        data->l = l;
        data->thread = i;
        pthread_create(&(threads[i]), NULL, needles, (void *)data);
    }
    for (int i = 0; i < MAX_THREADS; i++)
        pthread_join(threads[i], NULL);
    pthread_mutex_destroy(&mutex);
}

void *needles(void *estructura)
{
    structure_data *data = (structure_data *)estructura;
    double x, theta, n;
    long long iterations = data->iterations;
    double l = data->l;
    for (long long i = 0; i < iterations; i++)
    {
        x = (double)rand() / (double)(RAND_MAX / l);
        theta = (double)rand() / (double)(RAND_MAX / M_PI);
        n = sin(theta) / 2.0;
        if (x + n >= l || x - n <= 0)
        {
            pthread_mutex_lock(&mutex);
            add = add + 1;
            pthread_mutex_unlock(&mutex);
        }
    }
    if (data->thread == 0)
    {
        double resto = data->total_iterations % MAX_THREADS;

        for (int i = 0; i < resto; i++)
        {
            x = (double)rand() / (double)(RAND_MAX / l);
            theta = (double)rand() / (double)(RAND_MAX / M_PI);
            n = sin(theta) / 2.0;
            if (x + n >= l || x - n <= 0)
            {
                pthread_mutex_lock(&mutex);
                add = add++;
                pthread_mutex_unlock(&mutex);
            }
        }
    }

    return NULL;
}