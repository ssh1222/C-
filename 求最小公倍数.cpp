//��Ŀ����
//������A��������B ����С��������ָ �ܱ�A��B��������С��������ֵ�����һ���㷨��������A��B����С��������
//�������� :
//��������������A��B��
//������� :
//���A��B����С��������

#include <iostream>
using namespace std;

int gcb(int a, int b)
{
	int r;
	while (r = a % b){
		a = b;
		b = r;
	}
	return b;
}

int main()
{
	int a, b;
	while (cin >> a >> b)
		cout << a * b / gcb(a, b) << endl;
	return 0;
}