//�ҳ��ַ����е�һ��ֻ����һ�ε��ַ�
//
//
//
//
//�������� :
//����һ���ǿ��ַ���
//������� :
//�����һ��ֻ����һ�ε��ַ��������������� - 1
//ʾ��1
//����
//����
//asdfasdfo
//���
//����
//o

#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s;
	int i = 0;
	while (cin >> s){
		int arr[128] = { 0 };
		for (auto& e : s){
			arr[e]++;
		}
		for (i = 0; i < s.size(); i++){
			if (arr[s[i]] == 1){
				cout << s[i] << endl;
				break;
			}
		}
		if (i == s.size()){
			cout << -1 << endl;
		}
	}
	return 0;
}