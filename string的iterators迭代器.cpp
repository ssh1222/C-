//begin,end,rbegin,cend
//cbegin,cend,crbegin,crend(C++11)

//迭代器的返回值：如果basic_string对象是常量限定的，
//则函数返回一个const_iterator。
//否则，它返回一个迭代器。
//成员类型iterator和const_iterator是随机访问迭代器类型(分别指向一个字符和一个const字符)。
#include <iostream>
#include <string>
#include <stdlib.h>

//begin
//对于string来说，返回首元素的地址
//int main()
//{
//	std::string str("Test string");
//	for (std::string::iterator it = str.begin(); it != str.end(); ++it)
//		std::cout << *it;
//	std::cout << '\n';
//
//	system("pause");
//	return 0;
//}

//end
//对于string来说，返回字符串末尾元素的下一个位置的地址
//int main()
//{
//	std::string str("Test string");
//	for (std::string::iterator it = str.end(); it != str.begin(); --it){
//		if (it == str.end())
//			continue;
//		std::cout << *it;
//	}	
//	std::cout << *str.begin();
//	std::cout << '\n';
//
//	system("pause");
//	return 0;
//}

//rbegin
//对于string来说，返回字符串末尾元素的地址
//int main()
//{
//	std::string str("now step live...");
//	for (std::string::reverse_iterator rit = str.rbegin(); rit != str.rend(); ++rit)
//		std::cout << *rit;
//	std::cout << "\n";
//	system("pause");
//	return 0;
//}

//rend
//对于string来说，返回字符串首元素的上一个位置的地址
int main()
{
	std::string str("now step live...");
	for (std::string::reverse_iterator rit = str.rbegin(); rit != str.rend(); ++rit)
		std::cout << *rit;
	std::cout << "\n";
	system("pause");
	return 0;
}
