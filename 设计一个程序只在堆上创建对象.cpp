#include <iostream>
using namespace std;

//1.�������캯��
//2.�ṩ���еľ�̬����
//3.�����������죺1.C++ delete���� 2.˽�У�ֻ��������ʵ��
class Heap{
public:
	//static�������ʣ�1����.����  2.����::����
	static Heap* GetHeap() {
		return new Heap;
	}

	//1.C++11 delete����(��Ԫ�඼�޷�������)
	//Heap(const Heap& h) = delete;
private:
	Heap() {}
	//2.˽�У�ֻ��������ʵ�֣�ȱ�㣺��Ԫ����Ե��ã�
	Heap(const Heap& h) {}
};

int main(){
	Heap *ph = Heap::GetHeap();
	return 0;
}