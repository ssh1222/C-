//��Ŀ����
//����һ�� n * m �ľ��� a�������Ͻǿ�ʼÿ��ֻ�����һ��������ߣ���󵽴����½ǵ�λ�ã�·�������е������ۼ���������·���ͣ�������е�·������С��·���͡�
//�������� :
//��һ�������������� n �� m����ʾ����Ĵ�С��
//
//������ n ��ÿ�� m ��������ʾ����
//������� :
//���һ��������ʾ�𰸡�
//ʾ��1
//����
//����
//4 4
//1 3 5 9
//8 1 3 4
//5 0 6 1
//8 8 4 0
//���
//����
//12

#include<iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> v(n, vector<int>(m, 0));
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < m; ++j){
			cin >> v[i][j];
		}
	}
	vector<vector<int>> sumV(n + 1, vector<int>(m + 1, INT_MAX));
	sumV[1][1] = v[0][0];
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < m; ++j){
			if (i == 0 && j == 0)
				continue;
			int idx = i + 1;
			int idy = j + 1;
			sumV[idx][idy] = v[i][j] + min(sumV[idx - 1][idy], sumV[idx][idy - 1]);
		}
	}
	cout << sumV[n][m] << endl;
}