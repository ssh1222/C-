#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>

int main() {
	std::string str("adfadfcadadf");
	std::map<char, int> m;

	//将str添加到map中
	for (auto& e : str)
		++m[e];

	//找出出现次数最多的字符和最大次数
	int max = 0;
	for (auto& e : m){
		if (e.second > max)
			max = e.second;
	}
	std::cout << "最大次数：" << max << std::endl;
	//最多字符可能不止一个字符
	for (auto& e : m){
		if (e.second == max){
			str = e.first;
			std::cout << "字符：" << str << std::endl;
		}
	}
	
	system("pause");
	return 0;
}