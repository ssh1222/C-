//��Ŀ����
//��ʵ�����½ӿ�
//public   static   int  findNumberOf1(int num)
//{
//	/*  ��ʵ��  */
//	return  0;
//} Ʃ�磺����5 ��5�Ķ�����Ϊ101�����2
//
//�漰֪ʶ�㣺
//�������� :
//����һ������
//������� :
//����������������1�ĸ���

#include <iostream>
using namespace std;

int main()
{
	int n;
	while (cin >> n){
		int count = 0;
		while (n){
			if ((n & 1) == 1)
				count += 1;
			n >>= 1;
		}
		cout << count << endl;
	}
	return 0;
}