//��Ҷ�֪��쳲��������У�����Ҫ������һ������n���������쳲��������еĵ�n���0��ʼ����0��Ϊ0����
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