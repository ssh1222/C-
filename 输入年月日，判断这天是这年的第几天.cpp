//������������ڣ���������һ��ĵڼ��졣��
//��ϸ������
//����ĳ��ĳ��ĳ�գ��ж���һ������һ��ĵڼ��죿��


#include <iostream>

using namespace std;

int main()
{
	int year, month, day, sum;
	while (cin >> year >> month >> day){
		int array[] = { 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
		sum = array[month - 2];
		sum += day;
		if (month > 2){
			if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
				sum += 1;
		}
		cout << sum << endl;
	}
	return 0;
}