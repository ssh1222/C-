#include <iostream>
using namespace std;

//1.�������캯��
//2.�ṩstatic��������ջ�϶���
class Stack{
public:
	static Stack GetStack(){
		//�������Ż������ַ�����һ����������ֱ�ӷ���
		return Stack();
	}
private:
	Stack() {}
};
int main() {
	//���������޷����ù��캯��
	//Stack *p = new Stack();
	Stack s = Stack::GetStack();
	return 0;
}