#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y, t) {t=x; x=y; y=t;}
#define MAX_SIZE 10
#define NAME_SIZE 32

//adjust 함수의 구현은 수업시간에 다루었고 동일한 알로기즘으로 구현되어 있음
int list2[MAX_SIZE+1];
void adjust(int heap[], int root, int n)
{  
	int child = root*2;
	int temp = heap[root];

	while(child<=n){
		if(child<n && heap[child]<heap[child+1]){
			child++;
		}
		if(temp>heap[child]){
			break;
		}
		else{
			heap[child/2] = heap[child];
		}
		child *= 2;
	}
	heap[child/2] = temp;
}

void heap_sort(int list[], int n)
{  
	int i, temp;
	for(i=0;i<n;i++){
		list2[i] = list[i];
	}
	for(i=n/2;i>0;i--){
		adjust(list2,i,n);
	}
	for(i=n-1;i>0;i--){
		SWAP(list2[1],list2[i+1],temp);
		adjust(list2,1,i);
	}
	for(i=0;i<n;i++){
		list[i] = list2[i+1];
	}
}


void main()
{  
   FILE *f;
   int i;
   int list1[MAX_SIZE]; 
   f= fopen("input2.txt","r");
   fscanf(f,"%d %d %d %d %d %d %d %d %d %d",
	   &list1[0],&list1[1],&list1[2],&list1[3],&list1[4],
	   &list1[5],&list1[6],&list1[7],&list1[8],&list1[9]);
   //힙정렬
   heap_sort(list1, MAX_SIZE); /* 선택정렬 호출 */
   printf("heap_sort: \n");
   for(i=1; i<MAX_SIZE; i++) printf("%d \t", list1[i]);
   printf("\n");
}
