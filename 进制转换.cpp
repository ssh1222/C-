//题目描述
//给定一个十进制数M，以及需要转换的进制数N。将十进制数M转化为N进制数
//输入描述 :
//输入为一行，M(32位整数)、N(2 ≤ N ≤ 16)，以空格隔开。
//输出描述 :
//为每个测试实例输出转换后的数，每个输出占一行。如果N大于9，则对应的数字规则参考16进制（比如，10用A表示，等等）

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	string ret, table = "0123456789ABCDEF";
	bool flag = false;
	int m, n;
	cin >> m >> n;
	if (m < 0){
		m = 0 - m;
		flag = true;
	}

	while (m){
		ret += table[m % n];
		m /= n;
	}

	if (flag)
		ret += '-';
	//翻转字符串从begin位置到end-1位置
	reverse(ret.begin(), ret.end());
	cout << ret << endl;
	return 0;
}