//��Ŀ����
//Fibonacci��������������ģ�
//F[0] = 0
//F[1] = 1
//for each i �� 2: F[i] = F[i - 1] + F[i - 2]
//��ˣ�Fibonacci���о����磺0, 1, 1, 2, 3, 5, 8, 13, ...����Fibonacci�����е������ǳ�ΪFibonacci��������һ��N�����������Ϊһ��Fibonacci����ÿһ������԰ѵ�ǰ����X��ΪX - 1����X + 1�����ڸ���һ����N��������Ҫ���ٲ����Ա�ΪFibonacci����
//�������� :
//����Ϊһ��������N(1 �� N �� 1, 000, 000)
//������� :
//	 ���һ����С�Ĳ�����ΪFibonacci��"

#include<iostream>
using namespace std;

int main()
{
	int N, l, r, f, f0 = 0, f1 = 1;
	cin >> N;
	while (1){
		f = f0 + f1;
		f0 = f1;
		f1 = f;
		if (f < N){
			l = N - f;
		}
		else{
			r = f - N;
			break;
		}
	}
	cout << min(l, r) << endl;
	return 0;
}