//��Ŀ����
//һ�������� N ��Ԫ�أ�����������������͡� ���磺[-1, 2, 1]������������������Ϊ[2, 1]�����Ϊ 3
//��������:
//����Ϊ���С� ��һ��һ������n(1 <= n <= 100000)����ʾһ����n��Ԫ�� �ڶ���Ϊn��������ÿ��Ԫ��, ÿ����������32λint��Χ�ڡ��Կո�ָ���
//������� :
//���������������к�����ֵ��

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int size;
	cin >> size;
	vector<int> a(size);
	for (int i = 0; i < size; ++i)
		cin >> a[i];

	int ret = a[0];
	int sum1 = 0, sum2 = 0;
	for (int i = 0; i < size; ++i){
		sum2 = sum1 >= 0 ? sum1 + a[i] : a[i];
		if (sum2 > ret)
			ret = sum2;
		if (sum2 < 0)
			sum2 = 0;
		sum1 = sum2;
	}
	cout << ret << endl;
	return 0;
}