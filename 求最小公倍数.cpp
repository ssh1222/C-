//题目描述
//正整数A和正整数B 的最小公倍数是指 能被A和B整除的最小的正整数值，设计一个算法，求输入A和B的最小公倍数。
//输入描述 :
//输入两个正整数A和B。
//输出描述 :
//输出A和B的最小公倍数。

#include <iostream>
using namespace std;

int gcb(int a, int b)
{
	int r;
	while (r = a % b){
		a = b;
		b = r;
	}
	return b;
}

int main()
{
	int a, b;
	while (cin >> a >> b)
		cout << a * b / gcb(a, b) << endl;
	return 0;
}