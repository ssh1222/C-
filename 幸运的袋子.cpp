//���涼��һ������(ӵ����ͬ����������������)�����һ�����������˵ĵ��ҽ���������ĺ���ĺʹ���������ĺ���Ļ���
//���磺��������������ĺ�����{ 1, 1, 2, 3 }��������Ӿ������˵ģ���Ϊ1 + 1 + 2 + 3 > 1 * 1 * 2 * 3
//������ʵ��Ӵ������Ƴ�һЩ��(�����Ƴ�0��, ���Ǳ��Ƴ���)��Ҫʹ�Ƴ���Ĵ��������˵ġ����������̼���һ������Ի�õĶ����ֲ�ͬ�����˵Ĵ��ӡ�
//�������� :
//��һ������һ��������n(n �� 1000)
//�ڶ���Ϊn����������xi(xi �� 1000)
//������� :
//	 ������Բ��������˵Ĵ�����

#include <iostream>
#include <algorithm>
using namespace std;

int getLuckyPacket(int x[], int n, int pos, int sum, int multi)
{
	int count = 0;
	//ѭ����������λ��i��ʼ���п��ܵ����
	for (int i = pos; i < n; ++i){
		sum += x[i];
		multi *= x[i];
		if (sum > multi)
			count += 1 + getLuckyPacket(x, n, i + 1, sum, multi);
		else if (x[i] == 1)
			count += getLuckyPacket(x, n, i + 1, sum, multi);
		else
			break;
		sum -= x[i];
		multi /= x[i];
		while (i < n - 1 && x[i] == x[i + 1])
			++i;
	}
	return count;
}

int main()
{
	int n;
	while (cin >> n){
		int x[n];
		for (int i = 0; i < n; ++i)
			cin >> x[i];
		sort(x, x + n);
		cout << getLuckyPacket(x, n, 0, 0, 1) << endl;
	}
	return 0;
}