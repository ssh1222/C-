//一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字

class Solution {
public:
	void FindNumsAppearOnce(vector<int> data, int* num1, int *num2)
	{
		sort(data.begin(), data.end());
		int i = 0, flag = 0;
		while (i < data.size() - 1 && flag < 2){
			if (data[i] == data[i + 1]){
				i += 2;
				continue;
			}
			if (flag == 0){
				*num1 = data[i];
				++flag;
				++i;
				continue;
			}
			if (flag == 1){
				*num2 = data[i];
				++flag;
				++i;
			}
		}
		if (flag == 1)
			*num2 = data[i];
	}
};