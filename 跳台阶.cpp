//一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法（先后次序不同算不同的结果）。

class Solution {
public:
	int jumpFloor(int number)
	{
		if (number == 0 || number == 1)
			return 1;
		return jumpFloor(number - 1) + jumpFloor(number - 2);
	}
};