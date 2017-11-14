#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#define N 1000

//tim max cua 1 mang gom N phan tu, so sanh 2 truong hop chay 1 luong va chay da luong

int findMax(int *a, int n) {
	int max = a[0];
	for(int i=1; i<n; i++) {
		if(max > *(a+i)) max = *(a+i);
	}
}

int main() {
	int *a;
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
	#pragma omp parallel private(id, sid, eid,i)	//các lệnh dưới đây cùng nhau chạy trong từng luồng riêng rẽ nhau, số luồng đã đc set ở trên
	{
		id = omp_get_thread_num();		//lấy Id của luồng đang chạy, Id cua cac luong lan luot tu 0 den 9
		Nid = N/T;		// số lượng phần tử mỗi luồng, nghĩa là mỗi luồng sẽ lấy N phần tử rồi tìm max trong đó, sau đó lấy max của tất cả các luồng và so sánh
		sid=id*Nid;
		eid= sid + Nid;
		for(i=sid;i<eid;i++){
			if(max < *(a+i)) max = *(a+i);	//cach nay ko an toan vi co the xay ra tranh chap, khi 1 luong dang co gang so sanh gia tri cua max thi 1 luong khac lai ghi gia tri vao max, nen kq co the sai!
		}
	}

	printf("\n[chay da luong] Phan tu max cua a[] = %d \n",max);
	
	return 0;
}
