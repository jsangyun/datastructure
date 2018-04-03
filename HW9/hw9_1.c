#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y, t) {t=x; x=y; y=t;}
#define MAX_SIZE 10
#define NAME_SIZE 32

/* i는 정렬된 왼쪽리스트에 대한 인덱스
   j는 정렬된 오른쪽리스트에 대한 인덱스
   k는 정렬될 리스트에 대한 인덱스 */
void merge(int list[], int left, int mid, int right)
{  
   int i, j, k;
   int l;
   int mergeList[MAX_SIZE];
   i=left;  j=mid+1;  k=left;
   while ((i<=mid) && (j<=right)){
      if(list[i]<=list[j]){
	     mergeList[k] = list[i];
		 i++;
	  }
	  else{
	     mergeList[k] = list[j];
		 j++;
	  }
	  k++;
   }
   if(i>mid){
      for(l=j;l<=right;l++){
	     mergeList[k] = list[l];
		 k++;
	  }
   }
   else{
      for(l=i;l<=mid;l++){
	     mergeList[k] = list[l];
		 k++;
	  }
   }
   for(l=left;l<=right;l++){
      list[l]=mergeList[l];
   }
}

void merge_sort(int list[], int left, int right)
{  
   int mid;
   if(left<right){
      mid = (left+right)/2;     /* 리스트의 균등 분할 */
      merge_sort(list, left, mid);    /* 부분 리스트 정렬 */
      merge_sort(list, mid+1, right); /* 부분 리스트 정렬 */
	  merge(list, left, mid, right);    /* 합병 */
   }
}

void main()
{  
   FILE *f;
   int i;
   int list1[MAX_SIZE]; 
   f= fopen("input1.txt","r");
   fscanf(f,"%d %d %d %d %d %d %d %d %d %d",
	   &list1[0],&list1[1],&list1[2],&list1[3],&list1[4],
	   &list1[5],&list1[6],&list1[7],&list1[8],&list1[9]);

   //합병정렬
   merge_sort(list1, 0, MAX_SIZE-1); /* 선택정렬 호출 */
   printf("merge_sort: \n");
   for(i=0; i<MAX_SIZE; i++) printf("%d \t", list1[i]);
   printf("\n");
   fclose(f);
}
