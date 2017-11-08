#include<omp.h>
#include<stdio.h>

int main() {
	int i, id, sum, sid, eid, x;
	int n, t=10, a[100],b[100],c[100];
	printf	("Enter n, t: ");
	scanf("%d %d", &n, &t); 
	omp_set_num_threads(t);
	for(i=0;i<=100;i++){
	a[i]=i;
	b[i]=i^2;
}
	
	#pragma omp parallel private(id, x,i,sid,eid)
	{
		id = omp_get_thread_num();
		x = 10*id;
		sid=id*10;
		eid=(id+1)*10;
for(i=sid;i<=eid;i++){
	c[i]=a[i]+b[i];
}
	}
	for(i=0;i<=100;i++){
	printf("%d ",c[i]);
}
	
	return 0;
}
