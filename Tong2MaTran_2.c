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
	
	int Nidh, Nidc, id, idh, idc, sidh, sidc, eidh, eidc, Th = 3, Tc = 2;	//h = hang, c = cot
	omp_set_num_threads(Th*Tc);		//thiết lập số luồng để chạy

	#pragma omp parallel private(i, Nidh, Nidc, id, idh, idc, sidh, sidc, eidh, eidc)	//các lệnh dưới đây cùng nhau chạy trong từng luồng riêng rẽ nhau, số luồng đã đc set ở trên
	{
		//dung luong tinh theo hang
		id = omp_get_thread_num();
		idh = id/Tc; idc = id%Tc;
		Nidh = M/Th;	//=10/3=3
		Nidc = N/Tc;	//=6/2=3
		printf("Nidh = %d\n", Nidh);
		printf("Nidc = %d\n", Nidc);
		sidh = Nidh * idh; sidc = Nidc * idc;
		eidh = sidh + Nidh; eidc = sidc + Nidc;
		
		for(i=sidh; i<=eidh; i++) {
			for(j=sidc; j<=eidc; j++) {
				c[i][j] = a[i][j] + b[i][j];
			}
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
	printf("\nKq cua mang c[][]: \n");
	for(i=0; i<M; i++) {
		for(j=0; j<N; j++) {
			printf("%d ",c[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}
