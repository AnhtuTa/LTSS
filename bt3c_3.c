#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#define N 1000

//tim max cua 1 mang gom N phan tu, so sanh 2 truong hop chay 1 luong va chay da luong

int findMax(int *a, int s, int e) {		//VD: s=start=0, e=end=N
	int max = a[s];
	for(int j=s+1; j<e; j++) if(max < a[j]) max = a[j];
	return max;
}
int main() {
	int *a, *b;
	int i, Nid, id, sid, eid, T = 10;	//sid = startId, eid = endId, T = amount of threads
	int max;
	a = (int *)malloc(sizeof(int) * N);	//cấp phát động cho mảng a

	for(i=0; i<N; i++) {
		*(a+i) = rand()%1000 - 300;
		printf("%d ", *(a+i));
	}
	
	for(i=0; i<N; i++) {
		if(a[i] > max) max = a[i];
	}
	printf("\n[chay 1 luong] Phan tu max cua a[] = %d \n",max);
	max = 0;
	
	omp_set_num_threads(T);		//thiết lập số luồng để chạy
	b = (int *)malloc(sizeof(int) * T);

	#pragma omp parallel private(id, sid, eid,i)	//các lệnh dưới đây cùng nhau chạy trong từng luồng riêng rẽ nhau, số luồng đã đc set ở trên
	{
		id = omp_get_thread_num();		//lấy Id của luồng đang chạy, Id cua cac luong lan luot tu 0 den 9
		Nid = N/T;		// số lượng phần tử mỗi luồng, nghĩa là mỗi luồng sẽ lấy N phần tử rồi tìm max trong đó, sau đó lấy max của tất cả các luồng và so sánh
		sid=id*Nid;
		eid= sid + Nid;
		b[id] = findMax(a, sid, eid);
	}

	do {
		T = T/2;
		omp_set_num_threads(T);		//thiết lập số luồng để chạy
		#pragma omp parallel private(id)
		{
			id = omp_get_thread_num();
			b[id] = b[id]>b[id+T]?b[id]:b[id+T];
		}
	} while(T>1);

	printf("\n[chay da luong] Phan tu max cua a[] = %d \n",b[0]);
	
	return 0;
}
