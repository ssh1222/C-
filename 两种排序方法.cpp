//������n���ַ����ַ��������������ַ������ȶ��ǲ�ͬ�ġ��������ѧϰ���������ַ��������򷽷��� 1.�����ַ������ֵ����������磺
//"car" < "carriage" < "cats" < "doggies < "koala"
//2.�����ַ����ĳ����������磺
//"car" < "cats" < "koala" < "doggies" < "carriage"
//������֪���Լ�����Щ�ַ�������˳���Ƿ��������������򷽷�������Ҫæ�ų���Ҷ��������Ҫ������æ��֤��
//�������� :
//�����һ��Ϊ�ַ�������n(n �� 100)
//��������n��, ÿ��һ���ַ���, �ַ������Ⱦ�С��100������Сд��ĸ���
//������� :
//�����Щ�ַ����Ǹ����ֵ������ж����Ǹ��ݳ����������"lexicographically",
//
//������ݳ������ж������ֵ����������"lengths",
//
//������ַ�ʽ���������"both"���������"none"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<string> v;
	v.resize(n);
	for (auto& str : v)
		cin >> str;

	bool lenSym = true, lexSym = true;
	for (size_t i = 1; i < v.size(); ++i){
		if (v[i - 1].size() >= v[i].size()){
			lenSym = false;
			break;
		}
	}

	for (size_t i = 1; i < v.size(); ++i){
		if (v[i - 1] >= v[i]){
			lexSym = false;
			break;
		}
	}

	if (lenSym && lexSym)
		cout << "both" << endl;
	else if (lexSym)
		cout << "lexicographically" << endl;
	else if (lenSym)
		cout << "lengths" << endl;
	else
		cout << "none" << endl;
	return 0;
}