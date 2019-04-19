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
	//���캯��
	Vector() 
		:_start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{}

	//��������
	~Vector() {
		if (_start){
			delete[] _start;
			_start = _finish = _endOfStorage = nullptr;
		}
	}

	//β��
	void PushBack(const T& val) {
		if (_start){
			size_t newCapacity = _start == _finish ? 1 : 2 * Capacity();
			Reserve(newCapacity);
		}
		*_finish++ = val;
		Insert(end(), val);
	}

	//��������
	Vector(const Vector<T>& v) {
		//�������
		//���ռ�
		//����
		_start = new T[v.Capacity()];
		for (int i = 0; i < v.Size(); i++){
			_start[i] = v[i];
		}
		_finish = _start + v.Size();
		_endOfStorge = _start + v.Capaciyt();
	}

	//��ֵ���������
	Vector<T>& operator=(const Vector<T>& v) {
		//����Ƿ��Լ���ֵ
		//����ֵ���ͣ����ã�Ϊ��������ֵ
		//���أ�*this
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

	//����
	void Reserve(const size_t& n) {
		if (n > Capacity()){
			int len = Size();
			
			T* tmp = new T[n];

			//����ֱ��ʹ��memcpy���������
			//memcpy��ֵ������ǳ����
			//�����Զ������ͣ�������Դ�������ܻ������ռ�����ͷ�
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

	//Resize������Чֵ�ĸ���
	void Resize(size_t n, const T& val = T()) {
		if (n <= Size()){
			_finish = _start + n;
		}else{
			if (n > Capacity())
				Reserve(n);
			//����λ�ø�ֵ
			while (_finish != _start + n){
				*_finish = val;
				++_finish;
			}
		}
	}

	//βɾ
	void PopBack() {
		Erase(end() - 1);
	}

	//�ɶ���д
	T& operator[](size_t pos) {
		assert(pos < Size());
		return _start[pos];
	}

	//��������
	size_t Capacity() const {
		return _endOfStorage - _start;
	}

	//�п�
	bool Empty() {
		return _start == _finish;
	}

	//������Чֵ�ĸ���
	size_t Size() const{
		return _finish - _start;
	}

	//������
	//�ɶ���д
	//begin
	iterator begin() {
		return _start;
	}

	//end
	iterator end() {
		return _finish;
	}

	//ֻ��
	//begin
	const_iterator begin() const{
		return _start;
	}

	//end
	const_iterator end() const {
		return _finish;
	}

	//����
	iterator Insert(iterator pos, const T& val) {
		assert(pos <= _finish && pos >= _start);
		size_t len = pos - _start;
		//���ռ��Ƿ���
		if (_finish == _endOfStorage){
			size_t newC = _start == nullptr ? 1 : 2 * Capacity();
			Reserve(newC)
		}
		//����֮�󣬸��µ�����
		pos = _start + len;
		iterator end = _finish;
		//�Ӻ�����ǰŲ��Ԫ�أ��ڳ�pos�Ŀռ䣬����µ�Ԫ��val
		while (end > pos){
			*end = *(end - 1);
			end--;
		}

		*pos = val;
		++_finish;
		return pos;
	}

	//����ɾ�����ݵ���һ������
	//��������һ�߱���һ��ɾ���ĵ�����ʧЧ����
	iterator Erase(iterator pos) {
		assert(pos < _finish && pos >= _start);
		iterator begin = pos + 1;
		//��pos+1������ǰŲ��Ԫ��
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