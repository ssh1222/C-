//��Ŀ����
//����һ��ʮ������M���Լ���Ҫת���Ľ�����N����ʮ������Mת��ΪN������
//�������� :
//����Ϊһ�У�M(32λ����)��N(2 �� N �� 16)���Կո������
//������� :
//Ϊÿ������ʵ�����ת���������ÿ�����ռһ�С����N����9�����Ӧ�����ֹ���ο�16���ƣ����磬10��A��ʾ���ȵȣ�

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
	//��ת�ַ�����beginλ�õ�end-1λ��
	reverse(ret.begin(), ret.end());
	cout << ret << endl;
	return 0;
}