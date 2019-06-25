//��Ŀ����
//1
//1  1  1
//1  2  3  2  1
//1  3  6  7  6  3  1
//1  4  10 16 19  16 10  4  1
//���������ε����󣬵�һ��ֻ��һ����1������ÿ�е�ÿ��������ǡ������������������Ͻ��������Ͻǵ�����3����֮�ͣ����������ĳ��������Ϊ��������0����
//���n�е�һ��ż�����ֵ�λ�á����û��ż��������� - 1����������3, �����2������4�����3��
//
//����n(n <= 1000000000)
//��������:
//����һ��int����
//������� :
//������ص�intֵ

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int n, m;
	while (cin >> n){
		m = 2 * n - 1;
		vector<vector<int>> dp(n, vector<int>(m, 0));
		dp[0][0] = 1;
		for (int i = 1; i < n; i++){
			dp[i][0] = dp[i][2 * i] = 1;
			for (int j = 1; j < 2 * i; ++j){
				if (j == 1)
					dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
				else
					dp[i][j] = dp[i - 1][j - 2] + dp[i - 1][j - 1] + dp[i - 1][j];
			}
		}
		int k;
		for (k = 0; k < m; k++){
			if (dp[n - 1][k] % 2 == 0 && dp[n - 1][k] != 0){
				cout << k + 1 << endl;
				break;
			}
		}
		if (k == m)
			cout << -1 << endl;
	}

	return 0;
}