//��һ���ַ���ת����һ������(ʵ��Integer.valueOf(string)�Ĺ��ܣ�����string����������Ҫ��ʱ����0)��Ҫ����ʹ���ַ���ת�������Ŀ⺯���� ��ֵΪ0�����ַ�������һ���Ϸ�����ֵ�򷵻�0��
//�������� :
//����һ���ַ���, ����������ĸ����, ����Ϊ��
//������� :
//����ǺϷ�����ֵ����򷵻ظ����֣����򷵻�0

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
			//�жϵ�һ���ַ����ж�������
			if (*sit == '-' || *sit == '+'){
				if (*sit == '-'){
					flag = -1;
				}
			}
			else if (*sit < '0' || *sit > '9'){
				return 0;
			}
			else{
				//��ÿһ���ַ�ת��Ϊ�����������ۼ�
				ret *= 10;
				ret += *sit - '0';
			}
			++sit;
		}
		return ret * flag;
	}
};