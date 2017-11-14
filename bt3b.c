#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#define N 100

int main() {
	int *a;
	int i, Nid, id, sid, eid, T = 10;
	int sum;
	a = (int *)malloc(sizeof(int) * N);

	for(i=0; i<N; i++) {
		*(a+i) = i;
	}
	
	omp_set_num_threads(T);	
	
	#pragma omp parallel private(id, sid, eid,i)
	{
		id = omp_get_thread_num();
		Nid = N/T;
		sid=id*Nid;
		eid= sid + Nid;
		for(i=sid;i<eid;i++){
			sum += *(a+i);
		}
	}

	printf("Tong cac phan tu cua a[] = %d  ",sum);
	
	return 0;
}
