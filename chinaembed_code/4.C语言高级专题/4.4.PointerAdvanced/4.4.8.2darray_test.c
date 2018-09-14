#include <stdio.h>




int main(void)
{
	int a[2][5] = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}};
	//int a[2][5] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	
	printf("a[1][3] = %d.\n", a[1][3]);
	printf("a[1][3] = %d.\n", *(*(a+1)+3));
	
	//int *p1 = a;		// 类型不匹配
	//int **p2 = a;		// 类型不匹配
	
	// 指针指向二维数组的数组名
	int (*p3)[5];		// 数组指针，指针指向一个数组，数组有5个int类型元素
	p3 = a;				// a是二维数组的数组名，作为右值表示二维数组第一维的数组
						// 的首元素首地址，等同于&a[0]
	p3 = &a[0];
	
	printf("a[0][3] = %d.\n", *(*(p3+0)+3));
	printf("a[1][4] = %d.\n", *(*(p3+1)+4));
	
	// 指针指向二维数组的第一维
	//int *p4 = &a[0];		// 不可以
	int *p4 = a[0];			// a[0]表示二维数组的第一维的第一个元素，相当于是
							// 第二维的整体数组的数组名。数组名又表示数组首元素
							// 首地址，因此a[0]等同于&a[0][0];
	
	int *p5 = &a[0][0];	
	printf("a[0][4] = %d.\n", *(p4+4));
	int *p6 = a[1];
	printf("a[1][1] = %d.\n", *(p6+1));
	
	// 指向二维数组的第二维
	
	
	
	return 0;
}
















