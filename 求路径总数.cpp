//��Ŀ����
//���дһ�����������������Ӻ�����������n x m�����̸��ӣ�nΪ����ĸ�������mΪ����ĸ����������Ÿ��Ա�Ե�ߴ����Ͻ��ߵ����½ǣ��ܹ��ж������߷���Ҫ�����߻�ͷ·������ֻ�����Һ������ߣ���������������ߡ�
//�������� :
//��������������
//������� :
//���ؽ��

#include <iostream>
using namespace std;

int pathNum(int n, int m)
{
	if (n > 1 && m > 1)
		return pathNum(n - 1, m) + pathNum(n, m - 1);
	else if ((n == 1 && m >= 1) || (n >= 1 && m == 1))
		return n + m;
	else
		return 0;
}

int main()
{
	int a, b;
	while (cin >> a >> b)
		cout << pathNum(a, b) << endl;
	return 0;
}