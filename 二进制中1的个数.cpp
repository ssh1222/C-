//��Ŀ����
//����һ��������������������Ʊ�ʾ��1�ĸ��������и����ò����ʾ��

class Solution {
public:
	int  NumberOf1(int n)
	{
		int count = 0;
		unsigned int flag = 1;
		while (flag){
			if (n & flag)
				++count;
			flag = flag << 1;
		}
		return count;
	}
};