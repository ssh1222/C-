//题目描述
//将一句话的单词进行倒置，标点不倒置。比如 I like beijing.经过函数后变为：beijing.like I
//输入描述 :
//每个测试输入包含1个测试用例： I like beijing.输入用例长度不超过100
//输出描述 :
//依次输出倒置之后的字符串, 以空格分割

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	string s;
	getline(cin, s);
	reverse(s.begin(), s.end());
	auto start = s.begin();
	while (start != s.end()){
		auto end = start;
		while (end != s.end() && *end != ' ')
			++end;
		reverse(start, end);

		if (end != s.end())
			start = end + 1;
		else
			start = end;
	}

	cout << s << endl;
	return 0;
}