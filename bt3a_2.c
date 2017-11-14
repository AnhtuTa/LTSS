#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#define N 100

int main() {
	int *a, *b, *s;
	
	int i, Nid, id, sid, eid, T = 10;
	a = (int *)malloc(sizeof(int) * N);
	b = (int *)malloc(sizeof(int) * N);
	s = (int *)malloc(sizeof(int) * N);

	for(i=0; i<N; i++) {
		*(a+i) = 2*i;
		*(b+i) = i;
	}

	 
	omp_set_num_threads(T);
	
	
	#pragma omp parallel private(id, sid, eid,i)
	{
		id = omp_get_thread_num();
		Nid = N/T;
		sid=id*Nid;
		eid= sid + Nid;
		for(i=sid;i<eid;i++){
			*(s+i) = *(a+i) + *(b+i);
		}
	}

	for(i=0;i<N;i++){
		printf("%d  ",*(s+i));
	}
	
	return 0;
}
