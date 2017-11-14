#include<omp.h>
#include<stdio.h>

int main() {
	int id, x;
	omp_set_num_threads(100);	
	#pragma omp parallel
	{
		id = omp_get_thread_num();
		x = 10*id;
		printf("\n");
		int threads = omp_get_num_threads();
		printf("Hello from thread %d, x = %d\n", id, x);
		printf("\n");
	}
	return 0;
}
