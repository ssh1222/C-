#include <iostream>
#include <stdlib.h>

using namespace std;

class Date
{
public:
	//给变量赋值
	Date(int year = 2019, int month = 3, int day = 15)
	{
		if (year <= 0 || month <= 0 || month > 12
			|| day <= 0 || day > getDay(year, month)){
			cout << "非法日期，已设默认值为：2019-3-15" << endl;
			_year = 2019;
			_month = 3;
			_day = 15;
		}
		_year = year;
		_month = month;
		_day = day;
	}

	//拷贝构造函数
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	//赋值运算符重载
	Date& operator=(const Date& d)
	{
		if (this != &d){
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	}

	//获取一年中一月的天数
	int getDay(int year, int month)
	{
		int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day = days[month - 1];
		if (month == 2){
			//判断该年是否是闰年
			if ((year % 4 == 0 && year % 100 != 0)
				|| (year % 400 == 0))
				day++;
		}
		return day;
	}

	//+=的运算符重载
	Date& operator+=(int day)
	{
		if (day < 0)
			return *this -= -day;
		_day += day;
		while (_day > getDay(_year, _month)){
			//减去当月天数
			_day -= getDay(_year, _month);
			++_month;
			if (_month == 13){
				_month = 1;
				++_year;
			}
		}
		return *this;
	}

	//-=运算符重载
	Date& operator-=(int day) {
		if (day > 0)
			return *this += day;
		_day -= day;
		while (_day < 0){
			--_month;
			if (_month == 0){
				--_year;
				_month = 12;
			}
			_day += getDay(_year, _month);
		}
		return *this;
	}

	//+运算符重载
	Date operator+(int day) {
		Date ret(*this);
		ret += day;
		return ret;
	}

	//-运算符重载
	Date operator-(int day) {
		Date ret(*this);
		ret -= day;
		return *this;
	}

	//两个日期相减
	int operator-(const Date& d) {
		Date d1(*this);
		Date d2(d);
		int day = 0;
		if (d1 > d2){
			while (d1 > d2){
				--d1;
				++day;
			}
		}else{
			while (d1 < d2){
				++d1;
				--day;
			}
		}
		return day;
	}

	//++date
	Date& operator++(){
		return *this += 1;
	}

	//date--
	Date& operator++(int){
		Date ret(*this);
		*this += 1;
		return ret;
	}

	//--date
	Date& operator--() {
		return *this -= 1;
	}

	//date--
	Date& operator--(int) {
		Date ret(*this);
		*this -= 1;
		return ret;
	}

	//判断两个日期大小
	bool operator>(const Date& d)const{
		return (_year > d._year) ||
			((_year == d._year) && (_month > d._month)) ||
			((_month == d._month) && (_day > d._day));
	}

	bool operator>=(const Date& d)const {
		return (*this > d) || (*this == d);
	}

	bool operator<(const Date& d)const {
		return !(*this >= d);
	}
	bool operator<=(const Date& d)const {
		return !(*this > d);
	}

	bool operator==(const Date& d)const {
		return _year == d._year
			&& _month == d._month
			&& _day == d._day;
	}

	bool operator!=(const Date& d)const {
		return !(*this == d);
	}

	void display() {
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d1(2019, 3, 15);
	Date d2(2019, 12, 12);
	d1 += 60;
	d1.display();
	d2 -= 364;
	d2.display();
	cout << (d1 - d2) << endl;
	cout << (d1 > d2) << endl;
	system("pause");
	return 0;
	
}