//��һ�仰�ĵ��ʽ��е��ã���㲻���á����� I like beijing.�����������Ϊ��beijing.like I
//�������� :
//ÿ�������������1������������ I like beijing.�����������Ȳ�����100
//������� :
//�����������֮����ַ���, �Կո�ָ�

#include <iostream>
#include <string>

using namespace std;

int main()
{
	string s1, s2;
	cin >> s2;
	while (cin >> s1)
		s2 = s1 + " " + s2;
	cout << s2 << endl;
	return 0;
}