#include<stdio.h>
#include <stdlib.h>
void Bubble_sort(int k[],int n);
void Select_sort(int k[], int n);
void Merge_sort(int k[], int n);
void hebing(int* list_1, int list1_size, int* list_2, int list2_size);

int main(int argc, char* argv[]) {
	int k[100];
	int n, count,i,num;
		printf("请输入5个数字,我会为你从小到大排序\n");
		for (n = 0; n < 5; n++) {
			num=scanf_s("%d", &k[n],1);
		}

	
	do {
		printf("请选择排序方法：1.冒泡排序 2.选择排序 3.归并排序\n");
		scanf_s("%d", &count,2);
		switch (count)
		{
		case 1:Bubble_sort(k, n); break;
		case 2:Select_sort(k, n); break;
		case 3:Merge_sort(k, n); break;
		default:printf("哥，你输错了，请输入正确数字\n");
		}
	} while (count != 1 && count !=2 &&count !=3);

	printf("排序结果为：");
	for (i = 0; i < n ; i++) {
		printf("%d ", k[i]);
	}
	system("pause");

	return 0;


}

void Bubble_sort(int k[], int n) { //冒泡排序
	int i, j, temp;
	for (i = 0; i < n-1; i++) {
		for (j = 0;j<n-1; j++) {
			if (k[j]>k[j+1]) {
				temp = k[j];
				k[j] = k[j+1];
				k[j+1] = temp;
			}
			
		}
	} 

}

void Select_sort(int k[], int n) {//选择排序
	int i, j, temp, min;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j= i+1; j<n; j++){
			if (k[min]>k[j]){
				min = j;

			}

		}
		if (min != i) {
			temp = k[i];
			k[i] = k[min];
			k[min] =temp;
		}
	}

}

void hebing(int* list_1, int list1_size, int* list_2, int list2_size) {
	int temp_array[100];
	int i = 0,j = 0,k = 0,m;
	while (i<list1_size&&j<list2_size){
		if(list_1[i]>list_2[j]){
			temp_array[k++] = list_2[j++];
		}
		else{
			temp_array[k++] = list_1[i++];
		}
	}
	while(i < list1_size) {
		temp_array[k++] = list_1[i++];
	}

	while(j < list2_size) {
		temp_array[k++] = list_2[j++];
	}
	for (m=0,i=0; m< list1_size+list2_size; m++){
		list_1[m] = temp_array[m];
	}

	

}


void Merge_sort(int k[], int n) {
	if (n > 1) {
		int* list_1 = k;
		int list1_size = n / 2;
		int* list_2 = k + n / 2;
		int list2_size = n - list1_size;

		Merge_sort(list_1, list1_size);
		Merge_sort(list_2, list2_size);
	
		hebing(list_1, list1_size, list_2, list2_size);
	}
}

