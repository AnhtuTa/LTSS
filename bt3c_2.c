#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#define N 1000

//tim max cua 1 mang gom N phan tu, so sanh 2 truong hop chay 1 luong va chay da luong

int findMax(int *a, int n) {
	int max = a[0];
	for(int i=1; i<n; i++) {
		if(max < *(a+i)) max = *(a+i);	//lenh nay tuong duong voi: if(max < a[i]) max = a[i];
	}
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
		b[id] = a[sid];
		for(i=sid+1;i<eid;i++){
			if(b[id] < *(a+i)) b[id] = *(a+i);
		}
	}
	for(int j=0; j<T; j++) printf("b[%d] = %d\n", j, b[j]);
	int maxDaLuong = findMax(b, T);

	printf("\n[chay da luong] Phan tu max cua a[] = %d \n",maxDaLuong);
	
	return 0;
}
