//һֻ����һ�ο�������1��̨�ף�Ҳ��������2���������������һ��n����̨���ܹ��ж������������Ⱥ����ͬ�㲻ͬ�Ľ������

class Solution {
public:
	int jumpFloor(int number)
	{
		if (number == 0 || number == 1)
			return 1;
		return jumpFloor(number - 1) + jumpFloor(number - 2);
	}
};