//求1 + 2 + 3 + ... + n，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A ? B : C）。

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