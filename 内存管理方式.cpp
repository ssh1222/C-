#include <iostream>

//malloc��calloc��realloc������
//1.mallocֻ�ڶ�������һ�������Ŀռ䣻
//2.calloc�ڶ�������һ�������Ŀռ䲢���ռ䰴�ֽڳ�ʼ��Ϊ0��
//3.realloc���󣨻���С���Ѿ�����õĿռ䣺
//	1>ԭ�пռ����������ڴ��㹻���ռ���ʼλ�ò��䣻
//	2>���㣬��������һ�������Ŀռ䣬��ʼλ�øı䣻

//malloc��new������free��delete������
//1.����ռ�ʧ�ܣ�malloc����NULL��new���쳣
//2.����ռ䣺
//	1>�������ͣ�malloc��newû������
//	2>�Զ������ͣ�new����ù��캯��
//  �ͷſռ䣺
//  1>�������ͣ�delete��freeû������
//  2>�Զ����ͣ�delete�������������
//3.�᲻�����쳣��malloc���ᣬnew��

int main()
{
	//��̬����һ��int���͵Ŀռ�
	int *ptr = new int;

	//��̬����һ��int���͵Ŀռ䲢��ʼ��Ϊ10
	int *ptr1 = new int(10);

	//��̬����10��int���͵Ŀռ�
	int *ptr2 = new int[10];

	//��Ӧ���ͷſռ�
	delete ptr;
	delete ptr1;
	delete[] ptr2;
}