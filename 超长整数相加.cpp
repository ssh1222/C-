//��Ŀ����
//�����һ���㷨������������������ļӷ���
//
//�ӿ�˵��
//
//
///*
//�����һ���㷨������������������ļӷ���
//���������
//String addend������
//String augend��������
//����ֵ���ӷ����
//*/
//public String AddLongInteger(String addend, String augend)
//{
//	/*������ʵ�ֹ���*/
//
//	return null;
//}
//
//
//
//
//��������:
//���������ַ�������
//������� :
//�����Ӻ�Ľ����string��

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