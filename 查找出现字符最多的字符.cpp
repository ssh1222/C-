#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>

int main() {
	std::string str("adfadfcadadf");
	std::map<char, int> m;

	//��str��ӵ�map��
	for (auto& e : str)
		++m[e];

	//�ҳ����ִ��������ַ���������
	int max = 0;
	for (auto& e : m){
		if (e.second > max)
			max = e.second;
	}
	std::cout << "��������" << max << std::endl;
	//����ַ����ܲ�ֹһ���ַ�
	for (auto& e : m){
		if (e.second == max){
			str = e.first;
			std::cout << "�ַ���" << str << std::endl;
		}
	}
	
	system("pause");
	return 0;
}