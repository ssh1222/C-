//��Ŀ����
//����һ���������飬ʵ��һ�����������������������ֵ�˳��ʹ�����е�����λ�������ǰ�벿�֣�
//���е�ż��λ������ĺ�벿�֣�����֤������������ż����ż��֮������λ�ò��䡣

class Solution {
public:
	void reOrderArray(vector<int> &array)
	{
		vector<int> jisum;
		vector<int> ousum;
		for (int i = 0; i < array.size(); ++i){
			if (array[i] % 2 == 0)
				ousum.push_back(array[i]);
			else
				jisum.push_back(array[i]);
		}
		int i;
		for (i = 0; i < jisum.size(); ++i)
			array[i] = jisum[i];
		for (int j = i; j < array.size(); ++j)
			array[j] = ousum[j - i];
	}
};