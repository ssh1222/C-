//��Ŀ����
//��һ�仰�ĵ��ʽ��е��ã���㲻���á����� I like beijing.�����������Ϊ��beijing.like I
//�������� :
//ÿ�������������1������������ I like beijing.�����������Ȳ�����100
//������� :
//�����������֮����ַ���, �Կո�ָ�

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	string s;
	getline(cin, s);
	reverse(s.begin(), s.end());
	auto start = s.begin();
	while (start != s.end()){
		auto end = start;
		while (end != s.end() && *end != ' ')
			++end;
		reverse(start, end);

		if (end != s.end())
			start = end + 1;
		else
			start = end;
	}

	cout << s << endl;
	return 0;
}