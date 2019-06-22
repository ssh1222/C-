//��Ŀ����
//��ȫ����Perfect number�����ֳ����������걸������һЩ�������Ȼ����
//�����е������ӣ����������������Լ�����ĺͣ������Ӻ�������ǡ�õ���������
//���磺28������Լ��1��2��4��7��14��28����ȥ������28�⣬����5������ӣ�1 + 2 + 4 + 7 + 14 = 28��
//��������count(int n), ���ڼ���n����(��n)��ȫ���ĸ��������㷶Χ, 0 < n <= 500000
//����n������ȫ���ĸ����� �쳣������� - 1

#include <iostream>
#include <algorithm>
using namespace std;

int Count(int n)
{
	int count = 0;
	if ((n < 0) | (n > 500000))
		return -1;
	else{
		for (int i = 2; i <= n; ++i){
			int sum = 0;
			int sq = sqrt(i);
			for (int j = 2; j <= sq; ++j){
				if (i % j == 0){
					if (i / j == j)
						sum += j;
					else
						sum += j + (i / j);
				}
			}
			if (sum + 1 == i)
				count++;
		}
		return count;
	}
}

int main()
{
	int input;
	while (cin >> input)
		cout << Count(input) << endl;
	return 0;
}