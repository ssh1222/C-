//题目描述
//题目标题：
//计算两个字符串的最大公共字串的长度，字符不区分大小写
//详细描述：
//接口说明
//原型：
//int getCommonStrLength(char * pFirstStr, char * pSecondStr);
//输入参数：
//char * pFirstStr //第一个字符串
//char * pSecondStr//第二个字符串
//
//输入描述 :
//输入两个字符串
//输出描述 :
//输出一个整数

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int max = 0;
	string str1, str2;
	while (cin >> str1 >> str2){
		int len1 = str1.size();
		int len2 = str2.size();
		int max = 0;
		vector<vector<int>> dp(len1, vector<int>(len2, 0));
		for (int i = 0; i < len1; i++){
			for (int j = 0; j < len2; j++){
				if (str1[i] == str2[j]){
					if (i >= 1 && j >= 1)
						dp[i][j] = dp[i - 1][j - 1] + 1;
					else
						dp[i][j] = 1;
				}
				if (dp[i][j] > max)
					max = dp[i][j];
			}
		}
		cout << max << endl;
	}
	return 0;
}