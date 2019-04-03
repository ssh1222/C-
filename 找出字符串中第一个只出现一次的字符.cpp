//找出字符串中第一个只出现一次的字符
//
//
//
//
//输入描述 :
//输入一个非空字符串
//输出描述 :
//输出第一个只出现一次的字符，如果不存在输出 - 1
//示例1
//输入
//复制
//asdfasdfo
//输出
//复制
//o

#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s;
	int i = 0;
	while (cin >> s){
		int arr[128] = { 0 };
		for (auto& e : s){
			arr[e]++;
		}
		for (i = 0; i < s.size(); i++){
			if (arr[s[i]] == 1){
				cout << s[i] << endl;
				break;
			}
		}
		if (i == s.size()){
			cout << -1 << endl;
		}
	}
	return 0;
}