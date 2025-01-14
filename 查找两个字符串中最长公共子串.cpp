//题目描述
//查找两个字符串a, b中的最长公共子串。若有多个，输出在较短串中最先出现的那个。
//输入描述 :
//输入两个字符串
//输出描述 :
//返回重复出现的字符

#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	string str1, str2;
	while (cin >> str1 >> str2){
		if (str1.size() > str2.size())
			swap(str1, str2);
		int len1 = str1.size(), len2 = str2.size();
		int i, j, start = 0, max = 0;
		vector<vector<int>> MCS(len1 + 1, vector<int>(len2 + 1, 0));
		for (i = 1; i <= len1; i++){
			for (j = 1; j <= len2; j++){
				if (str1[i - 1] == str2[j - 1])
					MCS[i][j] = MCS[i - 1][j - 1] + 1;
				if (MCS[i][j] > max){
					max = MCS[i][j];
					start = i - max;
				}
			}
		}
		cout << str1.substr(start, max) << endl;
	}
	return 0;
}