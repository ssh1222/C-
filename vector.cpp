#include <iostream>
#include <string>
#include <assert.h>
#include <stdlib.h>

using namespace std;

template <class T>
class Vector{
	typedef T* iterator;
	typedef const T* const_iterator;
public:
	//构造函数
	Vector() 
		:_start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{}

	//析构函数
	~Vector() {
		if (_start){
			delete[] _start;
			_start = _finish = _endOfStorage = nullptr;
		}
	}

	//尾插
	void PushBack(const T& val) {
		if (_start){
			size_t newCapacity = _start == _finish ? 1 : 2 * Capacity();
			Reserve(newCapacity);
		}
		*_finish++ = val;
		Insert(end(), val);
	}

	//拷贝构造
	Vector(const Vector<T>& v) {
		//考虑深拷贝
		//开空间
		//拷贝
		_start = new T[v.Capacity()];
		for (int i = 0; i < v.Size(); i++){
			_start[i] = v[i];
		}
		_finish = _start + v.Size();
		_endOfStorge = _start + v.Capaciyt();
	}

	//赋值运算符重载
	Vector<T>& operator=(const Vector<T>& v) {
		//检查是否自己赋值
		//返回值类型：引用，为了连续赋值
		//返回：*this
		if (this != &v){
			T *tmp = new T[v.Capacity()];
			for (int i = 0; i < v.Size(); i++){
				tmp[i] = v[i];
			}

			if (_start)
				delete[] _start;
			_start = tmp;
			_finish = _start + v.Size();
			_endOfStorage = _start + v.Capacity();
		}
	}

	Vector<T>& operator=(const Vector<T> v) {
		Swap(v);
		return *this;
	}

	void Swap(Vector<T>& v) {
		swap(_start, v._start);
		swap(_finish, v._start);
		swap(_endOfStorage, v._endOfStorage);
	}

	//扩容
	void Reserve(const size_t& n) {
		if (n > Capacity()){
			int len = Size();
			
			T* tmp = new T[n];

			//这里直接使用memcpy是有问题的
			//memcpy：值拷贝，浅拷贝
			//对于自定义类型（含有资源），可能会引发空间二次释放
			//if (_start)
			//	memcpy(tmp, _start, sizeof(T)*len);
			if (_start){
				for (int i = 0; i < len; i++){
					tmp[i] = _start[i];
				}	
			}
			_start = tmp;
			_finish = _start + len;
			_endOfStorage = _start + n;
		}	
	}

	//Resize设置有效值的个数
	void Resize(size_t n, const T& val = T()) {
		if (n <= Size()){
			_finish = _start + n;
		}else{
			if (n > Capacity())
				Reserve(n);
			//新增位置赋值
			while (_finish != _start + n){
				*_finish = val;
				++_finish;
			}
		}
	}

	//尾删
	void PopBack() {
		Erase(end() - 1);
	}

	//可读可写
	T& operator[](size_t pos) {
		assert(pos < Size());
		return _start[pos];
	}

	//返回容量
	size_t Capacity() const {
		return _endOfStorage - _start;
	}

	//判空
	bool Empty() {
		return _start == _finish;
	}

	//返回有效值的个数
	size_t Size() const{
		return _finish - _start;
	}

	//迭代器
	//可读可写
	//begin
	iterator begin() {
		return _start;
	}

	//end
	iterator end() {
		return _finish;
	}

	//只读
	//begin
	const_iterator begin() const{
		return _start;
	}

	//end
	const_iterator end() const {
		return _finish;
	}

	//插入
	iterator Insert(iterator pos, const T& val) {
		assert(pos <= _finish && pos >= _start);
		size_t len = pos - _start;
		//检查空间是否够用
		if (_finish == _endOfStorage){
			size_t newC = _start == nullptr ? 1 : 2 * Capacity();
			Reserve(newC)
		}
		//增容之后，更新迭代器
		pos = _start + len;
		iterator end = _finish;
		//从后面向前挪动元素，腾出pos的空间，存放新的元素val
		while (end > pos){
			*end = *(end - 1);
			end--;
		}

		*pos = val;
		++_finish;
		return pos;
	}

	//返回删除数据的下一个数据
	//方便解决：一边遍历一边删除的迭代器失效问题
	iterator Erase(iterator pos) {
		assert(pos < _finish && pos >= _start);
		iterator begin = pos + 1;
		//从pos+1依次向前挪动元素
		while (begin < _finish){
			*(begin - 1) = *beign;
			++begin;
		}

		--_finish;
		return pos;
	}
	
private:
	T* _start;
	T* _finish;
	T* _endOfStorage;
};