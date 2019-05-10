//大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项（从0开始，第0项为0）。
//n <= 39

class Solution {
public:
	int Fibonacci(int n)
	{
		int sum = 0;
		int tmp = 1;
		if (n == 0){
			return sum;
		}
		if (n == 1){
			return tmp;
		}
		while (n--){
			int cur = sum;
			sum += tmp;
			tmp = cur;
		}
		return sum;
	}
};