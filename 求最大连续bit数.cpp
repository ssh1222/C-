//��Ŀ����
//���� : ��һ��byte���ֶ�Ӧ�Ķ�����������1�����������������3�Ķ�����Ϊ00000011���������2��1
//
// ���� : һ��byte�͵�����
//
//  ��� : ��
//
//   ���� : ��Ӧ�Ķ�����������1�����������
//	�������� :
//����һ��byte����
//������� :
//���ת�ɶ�����֮������1�ĸ���

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	int n;
	while (cin >> n){
		int count = 0, maxCount = 0;
		while (n){
			if (n & 1){
				++count;
				maxCount = max(count, maxCount);
			}
			else{
				count = 0;
			}
			n >>= 1;
		}
		cout << maxCount << endl;
	}
	return 0;
}