#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#define N 100

int main() {
	int *a;
	int i, Nid, id, sid, eid, T = 10;
	int max;
	a = (int *)malloc(sizeof(int) * N);

	for(i=0; i<N; i++) {
		//*(a+i) = -i*i + 10*i + 5;
		*(a+i) = rand*10();
		printf("%d ", *(a+i));
	}
a[4]=28;
	
	omp_set_num_threads(T);	
	
	#pragma omp parallel private(id, sid, eid,i)
	{
		id = omp_get_thread_num();
		Nid = N/T;
		sid=id*Nid;
		eid= sid + Nid;
		for(i=sid;i<eid;i++){
			if(max < *(a+i)) max = *(a+i);
		}
	}

	printf("Phan tu max cua a[] = %d \n",max);
	
	return 0;
}
