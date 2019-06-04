//题目描述
//功能 : 求一个byte数字对应的二进制数字中1的最大连续数，例如3的二进制为00000011，最大连续2个1
//
// 输入 : 一个byte型的数字
//
//  输出 : 无
//
//   返回 : 对应的二进制数字中1的最大连续数
//	输入描述 :
//输入一个byte数字
//输出描述 :
//输出转成二进制之后连续1的个数

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	int n;
	while (cin >> n){
		int count = 0, maxCount = 0;
		while (n){
			if (n & 1){
				++count;
				maxCount = max(count, maxCount);
			}
			else{
				count = 0;
			}
			n >>= 1;
		}
		cout << maxCount << endl;
	}
	return 0;
}