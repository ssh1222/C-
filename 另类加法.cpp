//��Ŀ����
//���дһ��������������������ӡ�����ʹ�� + �����������������
//��������int A��B���뷵��A��B��ֵ

#include<iostream>
using namespace std;

class UnusualAdd {
public:
	int addAB(int A, int B)
	{
		// write code here
		int sum = 0, carry = 0;
		while (B != 0){
			sum = A ^ B;
			carry = (A & B) << 1;
			A = sum;
			B = carry;
		}
		return sum;
	}
};