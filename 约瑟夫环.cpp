//���ӣ�https://www.nowcoder.com/questionTerminal/b28d83bef5414b7f814ae76c66b66ff8
//��Դ��ţ����
//
//���Ϊ0��n - 1��n����Χ��һȦ���ӱ��Ϊ0���˿�ʼ����1��������ȥ������m�����뿪����������µ�һ���ˣ�����Ƕ��٣�
//
//�������� :
//����һ����������n��m��3��n��106, 1��m��1003��n��10 ^ 6, 1��m��1003��n��106, 1��m��100��
//
//
//������� :
//������һ�����������˵ı�š�
//
//ʾ��1
//
//
//����
//8 3
//
//
//���
//6

#include <iostream>
using namespace std;

int Result(int n, int m)
{
	if (n == 1)
		return 0;
	else
		return (Result(n - 1, m) + m) % n;
}

int main()
{
	int n, m;
	cin >> n >> m;
	int ret = Result(n, m);
	cout << ret << endl;
	return 0;
}