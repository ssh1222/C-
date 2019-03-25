#include <iostream>
using namespace std;

//1.封死构造函数
//2.提供公有的静态方法
//3.封死拷贝构造：1.C++ delete函数 2.私有，只声明，不实现
class Heap{
public:
	//static方法访问：1对象.方法  2.类名::方法
	static Heap* GetHeap() {
		return new Heap;
	}

	//1.C++11 delete函数(友元类都无法被调用)
	//Heap(const Heap& h) = delete;
private:
	Heap() {}
	//2.私有，只声明，不实现（缺点：友元类可以调用）
	Heap(const Heap& h) {}
};

int main(){
	Heap *ph = Heap::GetHeap();
	return 0;
}