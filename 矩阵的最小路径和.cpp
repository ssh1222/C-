//题目描述
//给定一个 n * m 的矩阵 a，从左上角开始每次只能向右或者向下走，最后到达右下角的位置，路径上所有的数字累加起来就是路径和，输出所有的路径中最小的路径和。
//输入描述 :
//第一行输入两个整数 n 和 m，表示矩阵的大小。
//
//接下来 n 行每行 m 个整数表示矩阵。
//输出描述 :
//输出一个整数表示答案。
//示例1
//输入
//复制
//4 4
//1 3 5 9
//8 1 3 4
//5 0 6 1
//8 8 4 0
//输出
//复制
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