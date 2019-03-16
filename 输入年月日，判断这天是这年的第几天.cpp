//根据输入的日期，计算是这一年的第几天。。
//详细描述：
//输入某年某月某日，判断这一天是这一年的第几天？。


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