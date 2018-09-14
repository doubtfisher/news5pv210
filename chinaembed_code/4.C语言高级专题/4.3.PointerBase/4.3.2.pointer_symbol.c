#include <stdio.h>


int main(void)
{
	int a = 3, b = 5;
	
	a = b;		// 当a做左值时，我们关心的是a所对应的内存空间，而不是其中存储的3
	b = a;		// 当a做右值时，我们关心的是a所对应空间中存储的数，也就是5
	
	
	
/*
	int a;		// &a就表示a的地址。
	int *p;
	p = &a;		// 编译器一看到&a，就知道我们是要把变量a的地址赋值给指针变量p
				// 因为变量a的地址是编译器分配的，所以只有编译器才知道a的地址
				// 所以我们没法直接把a的地址的数字赋值给p，只有用符号&a来替代。
	
	// 理解&a，*p这样的符号，关键在于要明白当&和*和后面的变量结合起来后，就共同构成
	// 了一个新的符号，这个新的符号具有一定的意义。
*/
	
/*
	int a = 23;
	int b = 0;
	// 演示指针变量解引用
	int *p;							// *p就是我们说的星号的第一种用法
	p = &a;
	b = *p;			// b = 23		// *p就是我们说的星号的第二种用法
	printf("b = %d.\n", b);
*/	
	
/*
	// 演示指针变量定义

	// 把*和指针变量放在一起，而不是和int挨着，是为了一行定义多个变量时好理解
	int *p5, *p6;		// 这样才是定义了2个int *指针变量p5、p6
	int *p5, p6;		// p5是int *指针，p6是int的普通变量
	int* p5, p6;		// p5是int *指针，p6是int的普通变量
	
	// 实际编译测试，p1到p4都没有警告，说明4种写法编译器认为是一样的，都是定义了
	// int *类型的指针p
	int a = 4;
	int *p1;			// *和int结果，表明p的类型是int *，也就是
						// p是指向int类型变量的指针	
					
	int* p2;
	int*p3;
	int * p4;
	
	p1 = &a;
	p2 = &a;
	p3 = &a;
	p4 = &a;
*/
	
	return 0;
}




















