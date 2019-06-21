//��Ŀ����
//�ڵ����������n����ɫ�����ף����׷������֣�����ÿ����ɫ�����������׸�����һ����ͬ��A��������Ҫ���ţ�������Ҫȥ������ѡ���ס����ǻ谵�ĵƹ������޷��ֱ����׵���ɫ��ֻ�ֱܷ�������֡������������һЩ���ף�Ȼ��ѡ��һ˫��ɫ��ͬ�����������ס����ڵ������ǣ�������Ҫ�ö���ֻ����(���ּ�����)�����ܱ�֤һ����ѡ��һ˫��ɫ��ͬ�����ס�
//������ɫ����n(1��n��13), ͬʱ������������Ϊn������left, right, �ֱ����ÿ����ɫ���������׵����������ݱ�֤���ҵ�����������������26����һ����������һ�ֺϷ�������
//����������
//4, [0, 7, 1, 6], [1, 5, 0, 6]
//���أ�10(���ͣ�������������ȡ2ֻ����������ȡ8ֻ)

#include <iostream>
#include <vector>
using namespace std;

class Gloves {
public:
	int findMinimum(int n, vector<int> left, vector<int> right)
	{
		// write code here
		int left_sum = 0, left_min = INT_MAX;
		int right_sum = 0, right_min = INT_MAX;
		int sum = 0;
		for (int i = 0; i < n; ++i){
			if (left[i] * right[i] == 0)
				sum += left[i] + right[i];
			else{
				left_sum += left[i];
				right_sum += right[i];
				left_min = min(left_min, left[i]);
				right_min = min(right_min, right[i]);
			}
		}
		return sum + min(left_sum - left_min + 1, right_sum - right_min + 1) + 1;
	}
};