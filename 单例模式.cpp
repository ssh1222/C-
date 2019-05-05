#include <iostream>
using namespace std;

//�����������ò�������󣬶�Ҫ��ǰ׼���ã�
//1.���캯������Ϊ˽��
//2.����һ��������̬��Ա����̬��Ա�ڳ�������֮ǰ��ɳ�ʼ��
//3.�ṩһ����̬������ȡ������̬��Ա
//4.������

class Singleton1
{
public:
	//����ֵ����ֵ��ָ�룬��֤ȫ��Ψһ
	static Singleton1* GetInstance() {
		return &_sin;
	}
private:
	Singleton1()
	{}

	//���ַ�ʽ�����ԣ�1.������˽�У����Բ�ʵ��
	//               2.������һ��delete����
	//Singleton(const Singleton& s);
	Singleton1(const Singleton1& s) = delete;

	static Singleton1 _sin;
};

Singleton1 Singleton1::_sin;

#include <thread>
#include <mutex>

//����
//1.���캯��˽��
//2.������������
//3.�ṩ��̬�̰߳�ȫ�Ľӿڣ�double check�����Ч�ʣ�
//4.����һ����̬��������ָ�룬��ʼ��Ϊnullptr
//5.����ѡ������һ���ڲ��࣬�����ͷŵ���ָ��

class Singleton2{
public:
	static Singleton2* GetInstance() {
		//��ߺ����̵߳��ýӿ�Ч��
		if (_sin == nullptr){
			_mtx.lock();
			//��֤����ֻ�ܴ���һ�Σ���ֹ�ڴ�й¶
			if (_sin == nullptr){
				_sin = new Singleton2;
			}
			_mtx.unlock();
		}
		return _sin;
	}

	//~Singleton() {
	//	if (_sin){
	//		//������������ĵݹ����
	//		delete _sin;
	//		_sin = nullptr;
	//	}
	//}

	//�ڲ���
	class GC{
	public:
		~GC() {
			if (_sin){
				delete _sin;
				_sin = nullptr;
			}
		}
	};
private:
	Singleton2()
	{}

	Singleton2(const Singleton2& s);
	static Singleton2 *_sin;
	static mutex _mtx;
};

Singleton2* Singleton2::_sin = nullptr;
mutex Singleton2::_mtx;


