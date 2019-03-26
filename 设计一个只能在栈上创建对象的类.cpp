#include <iostream>
using namespace std;

//1.封死构造函数
//2.提供static方法产生栈上对象
class Stack{
public:
	static Stack GetStack(){
		//编译器优化：发现返回了一个匿名对象，直接返回
		return Stack();
	}
private:
	Stack() {}
};
int main() {
	//在类外面无法调用构造函数
	//Stack *p = new Stack();
	Stack s = Stack::GetStack();
	return 0;
}