//题目描述
//小Q得到一个神奇的数列 : 1, 12, 123, ...12345678910, 1234567891011...。
//
//			  并且小Q对于能否被3整除这个性质很感兴趣。
//
//			  小Q现在希望你能帮他计算一下从数列的第l个到第r个(包含端点)有多少个数可以被3整除。
//
//		  输入描述 :
//输入包括两个整数l和r(1 <= l <= r <= 1e9), 表示要求解的区间两端。
//输出描述 :
//输出一个整数, 表示区间内能被3整除的数字个数。
//示例1
//输入
//复制
//2 5
//输出
//复制
//3

#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int main()
{
	int l, r;
	while (scanf("%d %d", &l, &r) == EOF)
	{
		return 0;
	}
	int i;
	int count = 0;
	for (i = l; i <= r; i++)
	{
		if (i % 3 == 2 || i % 3 == 0)
			count++;
	}
	cout << count;
	return 0;
}
