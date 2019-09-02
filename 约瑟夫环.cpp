//链接：https://www.nowcoder.com/questionTerminal/b28d83bef5414b7f814ae76c66b66ff8
//来源：牛客网
//
//编号为0到n - 1的n个人围成一圈。从编号为0的人开始报数1，依次下去，报到m的人离开，问最后留下的一个人，编号是多少？
//
//输入描述 :
//输入一行两个整数n和m。3≤n≤106, 1≤m≤1003≤n≤10 ^ 6, 1≤m≤1003≤n≤106, 1≤m≤100。
//
//
//输出描述 :
//输出最后一个留下来的人的编号。
//
//示例1
//
//
//输入
//8 3
//
//
//输出
//6

#include <iostream>
using namespace std;

int Result(int n, int m)
{
	if (n == 1)
		return 0;
	else
		return (Result(n - 1, m) + m) % n;
}

int main()
{
	int n, m;
	cin >> n >> m;
	int ret = Result(n, m);
	cout << ret << endl;
	return 0;
}