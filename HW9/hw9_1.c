#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y, t) {t=x; x=y; y=t;}
#define MAX_SIZE 10
#define NAME_SIZE 32

/* i�� ���ĵ� ���ʸ���Ʈ�� ���� �ε���
   j�� ���ĵ� �����ʸ���Ʈ�� ���� �ε���
   k�� ���ĵ� ����Ʈ�� ���� �ε��� */
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
      mid = (left+right)/2;     /* ����Ʈ�� �յ� ���� */
      merge_sort(list, left, mid);    /* �κ� ����Ʈ ���� */
      merge_sort(list, mid+1, right); /* �κ� ����Ʈ ���� */
	  merge(list, left, mid, right);    /* �պ� */
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

   //�պ�����
   merge_sort(list1, 0, MAX_SIZE-1); /* �������� ȣ�� */
   printf("merge_sort: \n");
   for(i=0; i<MAX_SIZE; i++) printf("%d \t", list1[i]);
   printf("\n");
   fclose(f);
}
