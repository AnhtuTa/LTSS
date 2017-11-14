#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

#define M 8
#define N 8
#define P 9

//luu gia tri matrix A[M][N] trong 1 mang 1 chieu a[], vi vay: A[i][j] = a[i*N + j]
//(M = so hang, N = so cot)


void displayMatrix(int *a, int row, int col) {
	int i,j;
	for(i=0; i<row; i++) {
		for(j=0; j<col; j++) {
			printf("%d\t", *(a+i*col+j));
		}
		printf("\n");
	}
}

int main() {
	int i,j, starti, k, mc, id, nthreads, i1,i2, k1,k2, idh, idc;
	int NT = 6, NTh = 2, NTc = 3;
	int Ms, Ps;
	Ms = M/NTh;
	Ps = P/NTc;

	int *a, *b, *c;
	a = (int *) malloc (sizeof(int)*(M*N));
	b = (int *) malloc (sizeof(int)*(N*P));
	c = (int *) malloc (sizeof(int)*(M*P));
	
	//init arrays
	for(i=0; i<M; i++) 
		for(j=0; j<N; j++)
			*(a+i*N+j)=i+j;
	for(i=0; i<N; i++) 
		for(j=0; j<P; j++)
			*(b+i*P+j)=2*(i+j);
	for(i=0; i<M; i++) 
		for(j=0; j<P; j++)
			*(c+i*P+j)=0;
	
	omp_set_num_threads(NT);	
	#pragma omp parallel private(id, i, j, k, i1, i2, k1, k2)
	{
		id = omp_get_thread_num();
		idh = id/NTc; idc = id%NTc;
		i1 = Ms * idh; i2 = Ms*(idh+1);
		k1 = Ps * idc; k2 = Ps*(idc+1);
		
		//Nhan 2 matrix c = a * b
		for(i=i1; i<i2; i++) {
			for(k=k1; k<k2; k++) {
				for(j=0; j<N; j++) {
					*(c + i*P + k) = *(c+i*P+k) + (*(a+i*N+j)) * (*(b+j*P+k));
				}
			}
		}
	}
	
	printf("Matrix a:\n");
	displayMatrix(a, M, N);
	
	printf("\nMatrix b:\n");
	displayMatrix(b, N, P);
	
	printf("\nKq cua Matrix c: \n");
	displayMatrix(c, M, P);
	
	return 0;
}
