#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

double** A;
double** B;
double** C;
int num_of_threads = 3;
int size;


void create_matrix(int size,double** matrix){
    int i,j;
    int n = size;
    srand(time(NULL));
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            matrix[i][j] = rand() % 10;
        }
    }
}

void read_matrix(int size, double** matrix){
    int i,j;
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            printf("%.0lf\t",matrix[i][j]);
        }
        printf("\n");
   }
    printf("-------------------------------");
    printf("\n");
}

void *mult_matrix(void* rank);

int main(int argc,char** argv){
    int i,j;
    int size = atoi(argv[1]);
    int thread = atoi(argv[2]);
    pthread_t tid[num_of_threads];
    long rank;
    A = malloc(size*sizeof(double*)); 
    	for(i=0;i<size;i++)
        A[i]=malloc(size*sizeof(double));

  	B = malloc(size*sizeof(double*)); 
    	for(i=0;i<size;i++)
        B[i]=malloc(size*sizeof(double)); 
  
  	C = malloc(size*sizeof(double*)); 
    	for(i=0;i<size;i++)
    	C[i]=malloc(size*sizeof(double));

    clock_t start = clock();
	double spent_time = 0;
    create_matrix(size,A);
    // read_matrix(size,A);
    create_matrix(size,B);
    // read_matrix(size,B);
    for (rank = 0; rank < num_of_threads; rank++)
    pthread_create(&tid[rank], NULL,mult_matrix , (void*) rank);
    for (rank = 0; rank < num_of_threads; rank++)
    pthread_join(tid[rank], NULL);
	clock_t end = clock();
	spent_time = (double)(end - start) / CLOCKS_PER_SEC;
    FILE *f = fopen("result_threads.txt", "a");
    fprintf(f,"Tiempo de ejecucion: %.8f \n",spent_time);
    free(A);
    free(B);
    free(C);
    pthread_exit(NULL);
    return 0;
}


void *mult_matrix(void* id_arg){
    int i,j,p;
    long  id = (long ) id_arg;
    int size_per_thr = size/num_of_threads;
    int start_index = id*size_per_thr;
    int final_index = (id+1)*size_per_thr;
    for( i=start_index;i<final_index;i++){
		for( j=0;j<size;j++){
			for( p=0;p <size;p++){
				C[i][j] += A[i][p] * B[p][j];
			}	
		}
	}
}

