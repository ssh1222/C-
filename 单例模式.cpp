#include <iostream>
using namespace std;

//饿汉（不管用不用类对象，都要提前准备好）
//1.构造函数设置为私有
//2.定义一个单例静态成员，静态成员在程序运行之前完成初始化
//3.提供一个静态方法获取单例静态成员
//4.防拷贝

class Singleton1
{
public:
	//返回值引用值和指针，保证全局唯一
	static Singleton1* GetInstance() {
		return &_sin;
	}
private:
	Singleton1()
	{}

	//两种方式都可以：1.声明成私有，可以不实现
	//               2.声明成一个delete函数
	//Singleton(const Singleton& s);
	Singleton1(const Singleton1& s) = delete;

	static Singleton1 _sin;
};

Singleton1 Singleton1::_sin;

#include <thread>
#include <mutex>

//懒汉
//1.构造函数私有
//2.封死拷贝构造
//3.提供静态线程安全的接口（double check，提高效率）
//4.定义一个静态单例类型指针，初始化为nullptr
//5.（可选）定义一个内部类，辅助释放单例指针

class Singleton2{
public:
	static Singleton2* GetInstance() {
		//提高后续线程调用接口效率
		if (_sin == nullptr){
			_mtx.lock();
			//保证对象只能创建一次，防止内存泄露
			if (_sin == nullptr){
				_sin = new Singleton2;
			}
			_mtx.unlock();
		}
		return _sin;
	}

	//~Singleton() {
	//	if (_sin){
	//		//造成析构函数的递归调用
	//		delete _sin;
	//		_sin = nullptr;
	//	}
	//}

	//内部类
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


