#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

#define M 2
#define N 3
#define P 5


int main() {
	int i,j, starti, k, mc, id, nthreads;
/*
	int a[M][N];
	int b[N][P];
	int c[M][P];
	
	d
	for(i=0; i<M; i++) {
		for(j=0; j<N; j++) {
			a[i][j]=i+j;
			b[i][j]=2*i+2*j;
		}
	}
	*/
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
	
	omp_set_num_threads(2);	
	#pragma omp parallel private(id, starti, i, j, k)
	{
		nthreads = omp_get_num_threads();
		id = omp_get_thread_num();
		mc = M/nthreads;
		starti = id*mc;
		for(i=starti; i<starti+mc; i++) {
			for(j=0; j<P; j++) {
				for(k=0; k<N; k++) {
					*(c + i*P + j) = *(c+i*P+j) + (*(a+i*N+k)) * (*(b+k*P+j));
				}
			}
		}
	}
	
	printf("Mang a:\n");
	for(i=0; i<M; i++) {
		for(j=0; j<N; j++) {
			printf("%d ",*(a+i*N+j));
		}
		printf("\n");
	}
	printf("\nMang b:\n");
	for(i=0; i<N; i++) {
		for(j=0; j<P; j++) {
			printf("%d ",*(b+i*P+j));
		}
		printf("\n");
	}
	printf("\nKq cua mang c[][]: \n");
	for(i=0; i<M; i++) {
		for(j=0; j<P; j++) {
			printf("%d ",*(c+i*P+j));
		}
		printf("\n");
	}
	
	return 0;
}
