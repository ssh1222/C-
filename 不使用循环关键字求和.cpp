//��1 + 2 + 3 + ... + n��Ҫ����ʹ�ó˳�����for��while��if��else��switch��case�ȹؼ��ּ������ж���䣨A ? B : C����

class Solution {
public:
	class Sum{
	public:
		Sum()
		{
			sum += i;
			i++;
		}
	};
	int Sum_Solution(int n)
	{
		sum = 0;
		i = 1;
		Sum arr[n];
		return sum;
	}
private:
	static int sum;
	static int i;
};

int Solution::sum = 0;
int Solution::i = 1;