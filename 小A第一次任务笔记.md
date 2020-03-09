#**Section 1**
---
 <font size=4 face="黑体">因为假期有很长一段时间没用C语言了，趁此机会复习+学新知识，复习了两种排序，又新掌握了1种排序</font>

<font size=5 face="微软雅黑">**冒泡排序** </font>

		void Bubble_sort(int k[], int n) {  
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

<font size=4 face="黑体">最简单的排序，k[]中存储着未排列的数字，n为数字的个数，用i，j分别作为外层循环与内层嵌套循环的计数器，若有n个数待排列则外层只需n-1次，内层循环实现从数组第一个元素开始依次两两比较，数组中较前的元素若大于下一位元素则进行值的对换，一次内层循环完成则排好一个数，时间复杂度为O(n^2),效率较低。</font>

<font size=5 face="微软雅黑">**选择排序** </font>

	void Select_sort(int k[], int n) {//选择排序
	int i, j, temp, min;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for(j=i+1;j<n;j++){
			if (k[min] > k[j]) {
				min = j;
			}
		}
			
		if (min!=i){
			temp = k[i];
			k[i] = k[min];
			k[min] = temp;
		}

	}
	}
<font size=4 face="黑体">函数形参与冒泡排序的一致，函数中外层循环中多定义了一个min用于在每次循环开始时将第一个比较的数假设为最小值，嵌套循环中将假设的最小值与后面的值一一比较，当遇到比最小值还小的数时则记录这个数的位置，退出嵌套循环后如果min不等于原来的i则将记录的真正的最小值赋予给i所在位置，该排列时间复杂度为O(n)</font>

<font size=5 face="微软雅黑">**归并排序** </font>

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
<font size=4 face="黑体">**第一个为实现合并过程的函数，第二个为实现拆分过程的函数**  
<font size=4 face="黑体">先分析拆分过程的函数，形参依旧是一个数组和排列数字数量，该函数用途是将一个数列分为两个数列，再通过递归不断细分直至单个数列中数字只有1个时停止。第一次定义list_1的地址在k[0]处，list2地址在k[n/2]处，第一次运行时list1size为原数列数量一半，list2size为剩余数量，然后分两条路传入不同的形参调用两次自身分别进行拆分，if语句为退出递归的条件，即拆分至list1/2size=1时退出递归，然后一层层返回的过程中一次次的调用hebing函数。</font>  
<font size=4 face="黑体">而hebing函数实现的是从最小的size只有1的数列开始两两有序合并，我先设置了一个临时数组用于存放单次合并完成的数列，并初始化了i,j,m,三个计数器，第一个while用"与"判断list1和list2中是否同时拥有没有排列的数字，有则进行从小到大排列，第二个和第三个while用于判断是哪个list中存在没有排列的数,因为一定会存在一个数只剩它自己，没有办法比较(这个数一定为这次合并的最大值，所以放在单次合并的最后一个位置),该函数最后一个for循环是指每次合并都将所有已排列好的数存放进list1中，然后再进行下次合并</font>  

<font size=4 face="黑体">以上就是我的程序分析，这次复习+新学习用了我挺长时间的，一是太久没练，二是递归是真的难，但是能理解并写出来后还是很有成就感的，希望再接再厉，打好基础！</font>

#**Section 2**
---
学习日记  

<font size=4 face="黑体"> 简单说一下，最近接触c语言就是完成任务这次，还有练习单片机时用keil4有用过，C语言的话之前是自学完指针，还有结构体啥的，但没有深入研究数据结构和算法，能基本使用C语言操作单片机，最近也没有深入了解C，因为在弄单片机。(其实上面程序分析就是相当于学习报告了)</font>