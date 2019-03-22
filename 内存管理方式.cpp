#include <iostream>

//malloc、calloc、realloc的区别
//1.malloc只在堆上申请一段连续的空间；
//2.calloc在堆上申请一段连续的空间并将空间按字节初始化为0；
//3.realloc扩大（或缩小）已经申请好的空间：
//	1>原有空间后面扩充的内存足够，空间起始位置不变；
//	2>不足，重新申请一段连续的空间，起始位置改变；

//malloc与new的区别、free与delete的区别
//1.申请空间失败：malloc返回NULL，new抛异常
//2.申请空间：
//	1>内置类型：malloc和new没有区别
//	2>自定义类型：new会调用构造函数
//  释放空间：
//  1>内置类型：delete和free没有区别
//  2>自定类型：delete会调用析构函数
//3.会不会抛异常：malloc不会，new会

int main()
{
	//动态申请一个int类型的空间
	int *ptr = new int;

	//动态申请一个int类型的空间并初始化为10
	int *ptr1 = new int(10);

	//动态申请10个int类型的空间
	int *ptr2 = new int[10];

	//对应的释放空间
	delete ptr;
	delete ptr1;
	delete[] ptr2;
}