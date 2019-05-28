//��Ŀ����
//����һ���ַ����������һ���㷨���ж����Ƿ�Ϊһ���Ϸ������Ŵ���
//����һ���ַ���A�����ĳ���n���뷵��һ��boolֵ�������Ƿ�Ϊһ���Ϸ������Ŵ���
////����������
//"(()())", 6
//���أ�true
//����������
//"()a()()", 7
//���أ�false
//����������
//"()(()()", 7
//���أ�false
#include <iostream>
#include <stack>
using namespace std;

class Parenthesis {
public:
	bool chkParenthesis(string A, int n)
	{
		stack<char> s;
		for (auto e : A){
			switch (e){
			case '(':
				s.push(e);
				break;
			case')':{
						if (s.empty() || s.top() != '(')
							return false;
						else
							s.pop();
			}
				break;
			default:
				return false;
			}
		}
		return true;
	}
};