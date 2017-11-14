#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

#define M 10	//so hang
#define N 6		//so cot

int main() {
	int a[M][N];
	int b[M][N];
	int c[M][N];
	int i,j;
	
	for(i=0; i<M; i++) {
		for(j=0; j<N; j++) {
			a[i][j]=i+j;
			b[i][j]=2*i+2*j;
		}
	}
	
	printf("Mang a:\n");
	for(i=0; i<M; i++) {
		for(j=0; j<N; j++) {
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	printf("\nMang b:\n");
	for(i=0; i<M; i++) {
		for(j=0; j<N; j++) {
			printf("%d ",b[i][j]);
		}
		printf("\n");
	}
	
	int Nid, id, sid, eid, T = 5;	//sid = startId, eid = endId, T = amount of threads
	omp_set_num_threads(T);		//thiết lập số luồng để chạy
	Nid = M/T;	//the amount of rows each thread handles (so luong hang ma moi thread xu ly)

	#pragma omp parallel private(id, sid, eid,i)	//các lệnh dưới đây cùng nhau chạy trong từng luồng riêng rẽ nhau, số luồng đã đc set ở trên
	{
		//dung luong tinh theo hang
		id = omp_get_thread_num();
		sid = id*Nid;
		eid = sid + Nid;
		for(i=sid; i<eid; i++) {	//co 5 thread, moi thread se tinh tong cua 2 hang
			for(j=0; j<N; j++) {
				c[i][j] = a[i][j] + b[i][j];
			}
		}
	}
	
	printf("\nKq cua mang c[][]: \n");
	for(i=0; i<M; i++) {
		for(j=0; j<N; j++) {
			//printf("%d ", c[i][j]);
			printf("%d ",c[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}
