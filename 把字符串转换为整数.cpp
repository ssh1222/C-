//将一个字符串转换成一个整数(实现Integer.valueOf(string)的功能，但是string不符合数字要求时返回0)，要求不能使用字符串转换整数的库函数。 数值为0或者字符串不是一个合法的数值则返回0。
//输入描述 :
//输入一个字符串, 包括数字字母符号, 可以为空
//输出描述 :
//如果是合法的数值表达则返回该数字，否则返回0

#include <string>
#include <iostream>

class Solution {
public:
	int StrToInt(string str)
	{
		int ret = 0;
		int flag = 1;
		string::iterator sit = str.begin();
		while (sit != str.end()){
			//判断第一个字符，判断正负数
			if (*sit == '-' || *sit == '+'){
				if (*sit == '-'){
					flag = -1;
				}
			}
			else if (*sit < '0' || *sit > '9'){
				return 0;
			}
			else{
				//将每一个字符转化为整数，再做累加
				ret *= 10;
				ret += *sit - '0';
			}
			++sit;
		}
		return ret * flag;
	}
};