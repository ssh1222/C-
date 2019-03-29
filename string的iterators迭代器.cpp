//begin,end,rbegin,cend
//cbegin,cend,crbegin,crend(C++11)

//�������ķ���ֵ�����basic_string�����ǳ����޶��ģ�
//��������һ��const_iterator��
//����������һ����������
//��Ա����iterator��const_iterator��������ʵ���������(�ֱ�ָ��һ���ַ���һ��const�ַ�)��
#include <iostream>
#include <string>
#include <stdlib.h>

//begin
//����string��˵��������Ԫ�صĵ�ַ
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
//����string��˵�������ַ���ĩβԪ�ص���һ��λ�õĵ�ַ
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
//����string��˵�������ַ���ĩβԪ�صĵ�ַ
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
//����string��˵�������ַ�����Ԫ�ص���һ��λ�õĵ�ַ
int main()
{
	std::string str("now step live...");
	for (std::string::reverse_iterator rit = str.rbegin(); rit != str.rend(); ++rit)
		std::cout << *rit;
	std::cout << "\n";
	system("pause");
	return 0;
}
