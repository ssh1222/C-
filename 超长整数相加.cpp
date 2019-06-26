//题目描述
//请设计一个算法完成两个超长正整数的加法。
//
//接口说明
//
//
///*
//请设计一个算法完成两个超长正整数的加法。
//输入参数：
//String addend：加数
//String augend：被加数
//返回值：加法结果
//*/
//public String AddLongInteger(String addend, String augend)
//{
//	/*在这里实现功能*/
//
//	return null;
//}
//
//
//
//
//输入描述:
//输入两个字符串数字
//输出描述 :
//输出相加后的结果，string型

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string addStrings(string num1, string num2)
{
	int i = num1.size() - 1;
	int j = num2.size() - 1;
	string result = "";
	int carry = 0;
	while (i >= 0 || j >= 0){
		if (i >= 0)
			carry += num1[i] - '0';
		if (j >= 0)
			carry += num2[j] - '0';
		result += (char)(carry % 10 + '0');
		carry /= 10;
		i--;
		j--;
	}

	if (carry == 1)
		result += '1';
	reverse(result.begin(), result.end());
	return result;
}

int main()
{
	string s1, s2;
	while (cin >> s1 >> s2)
		cout << addStrings(s1, s2) << endl;
	return 0;
}