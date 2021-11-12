#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <math.h>

long long monte_carlo(pid_t *, double *, long long);
void darts(double *, long long, long long, int);

#define MAX_PROCESS 8

int main(int argc, char *argv[])
{
    int i, j, n, pid, status, size_of_iteration_process;
    long long iterations = atoll(argv[1]);
    double pi;
    size_of_iteration_process = iterations / n;
    long long circle = 0;
    double *adds = NULL;
    adds = (double *)mmap(NULL, sizeof(double *) * MAX_PROCESS, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 1, 0);
    n = 4;
    srand(time(NULL));
    pid_t *forks = (pid_t *)malloc(MAX_PROCESS * sizeof(pid_t));
    clock_t start = clock();
    circle = monte_carlo(forks, adds, iterations);
    pi = 4.0 * circle / (double)iterations;
    clock_t end = clock();
    float segundos = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Pi: %lf\nLa ejecucion ha tomado %.8f segundos\n", pi, segundos);
    return 0;
}

long long monte_carlo(pid_t *forks, double *adds, long long iterations)
{
    double x, y, d;
    long long add = 0;
    long long iter_per_process = iterations / MAX_PROCESS;

    for (int i = 0; i < MAX_PROCESS; i++)
    {
        if ((forks[i] = fork()) < 0)
        {
            perror("fork");
            abort();
        }
        else if (forks[i] == 0)
        {
            darts(adds, iterations, iter_per_process, i);
            exit(0);
        }
    }

    for (int i = 0; i < MAX_PROCESS; i++)
        wait(NULL);
    for (int i = 0; i < MAX_PROCESS; i++)
        add += adds[i];
    return add;
}

void darts(double *adds, long long iterations, long long iter_per_process, int process)
{
    double x, y, d;
    adds[process] = 0;
    for (long long i = 0; i < iter_per_process; i++)
    {
        //Genera una coordenada (x,y)
        x = (double)rand() / (double)(RAND_MAX / 2);
        x = x - 1;
        y = (double)rand() / (double)(RAND_MAX / 2);
        y = y - 1;
        //Calcula si el dardo cae en el circulo
        d = (x * x) + (y * y);
        if (d <= 1)
            adds[process] = adds[process] + 1;
    }

    if (process == 0)
    {
        double aux = iterations % MAX_PROCESS;
        for (int i = 0; i < aux; i++)
        {
            x = (double)rand() / (double)(RAND_MAX / 2);
            x = x - 1;
            y = (double)rand() / (double)(RAND_MAX / 2);
            y = y - 1;
            d = sqrt((x * x) + (y * y));
            if (d <= 1)
                adds[process] += 1;
        }
    }
}
