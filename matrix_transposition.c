#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void create_matrix(int size, double **matrix)
{
    int i, j;
    int n = size;
    srand(time(NULL));
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            matrix[i][j] = rand() % 10;
}

void mult_matrix(double **A, double **B, double **C, int size)
{
    int i, j, p;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            for (p = 0; p < size; p++)
                C[i][j] += A[i][p] * B[j][p];
}

void transposition(int size, double **B, double **D)
{
    int i, j;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            D[j][i] = B[i][j];
}

void read_matrix(int size, double **matrix)
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
            printf("%.0lf\t", matrix[i][j]);
        printf("\n");
    }
    printf("-------------------------------");
    printf("\n");
}

int main(int argc, char **argv)
{
    int i, j;
    int size = atoi(argv[1]);
    double **A = malloc(size * sizeof(double *));
    for (i = 0; i < size; i++)
        A[i] = malloc(size * sizeof(double));

    double **B = malloc(size * sizeof(double *));
    for (i = 0; i < size; i++)
        B[i] = malloc(size * sizeof(double));

    double **C = malloc(size * sizeof(double *));
    for (i = 0; i < size; i++)
        C[i] = malloc(size * sizeof(double));

    double **D = malloc(size * sizeof(double *));
    for (i = 0; i < size; i++)
        D[i] = malloc(size * sizeof(double));

    clock_t start = clock();
    double spent_time = 0;
    create_matrix(size, A);
    // read_matrix(size, A);
    create_matrix(size, B);
    // read_matrix(size, B);
    transposition(size, B, D);
    // read_matrix(size, D);
    mult_matrix(A, D, C, size);
    // read_matrix(size, C);
    clock_t end = clock();
    spent_time = (double)(end - start) / CLOCKS_PER_SEC;
    FILE *f = fopen("result_transposition.txt", "a");
    fprintf(f, "Tiempo de ejecucion: %.8f \n", spent_time);
    return 0;
}
