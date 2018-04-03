#include <stdio.h>
#define MAX_SIZE 100
#define SWAP(x,y,z) ((t) = (x), (x) = (y), (y) = (t))

int n= 9;
int list[MAX_SIZE] = {9,8,7,6,5,4,3,2,1};

void print(int list[], int n){
	int i;
	for(i=0; i<n; i++){
		printf("%d", list[i]);
	}
	printf("\n");
}

int partition(int v[], int left, int right){
	int ipivot = (left+right)/2; //피봇은 선택
	int store = -1; //초기화를 위해 임의의 값 -1을 택함
	int i = 0;
	
	int swap = v[ipivot];
	v[ipivot] = v[right];
	v[right] = swap;
	
	store = left;
	
	for(i = left; i<right; i++){
		if(v[i] <= v[right]){
			swap = v[i];
			v[i] = v[store];
			v[store] = swap;
			
			store++;
		}
	}
	
	swap = v[store];
	v[store] = v[right];
	v[right] = swap;
	
	return store;
}

void quick_sort(int list[], int left, int right){
	if(left<right){
		int q = partition(list, left, right);
		print(list,9);
		quick_sort(list, left, q-1);
		quick_sort(list, q+1, right);
	}
}

int main(){
	quick_sort(list, 0, 8);
}

