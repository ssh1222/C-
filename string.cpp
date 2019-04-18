#include <iostream>
#include <assert.h>
using namespace std;

class String{
public:
	typedef char* iterator;
	typedef const char* const_iterator;
	//���캯��
	String(char *str = ""){
		assert(str != nullptr);
		//_size:��Ч�ַ�������������'\0'
		_size = strlen(str);
		_str = new char[_size + 1];
		strcpy(_str, str);//while(*str1++ = *str2++);
		_capacity = _size;
	}
	//��������
	String(const String& s) 
		:_str(nullptr)
		, _size(0)
		, _capacity(0)
	{
		String tmp(s._str);
		Swap(tmp);
	}

	//��������
	void Swap(String& s) {
		swap(_str, s._str);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}

	//��ֵ���������
	String& operator=(String s){
		Swap(s);
		return *this;
	}

	//[]��ʽ�����ַ�,�ɶ��ɸ�
	char& operator[](size_t pos) {
		assert(pos < _size);
		return _str[pos];
	}

	//[]ֻ�������ɸ�
	const char& operator[](size_t pos) const {
		assert(pos < _size);
		return _str[pos];
	}

	//��������ʹ��
	//����beginλ�ã��ɶ���д
	iterator begin() {
		return _str;
	}

	//����end��λ�ã��ɶ���д
	iterator end() {
		return _str + _size;
	}

	//����beginλ�ã�ֻ��
	const_iterator begin()const {
		return _str;
	}

	//����endλ�ã�ֻ��
	const_iterator end()const {
		return _str + _size;
	}

	//��������
	~String(){
		if (_str){
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
	}

	char* c_str(){
		return _str;
	}

	//��β������
	void PushBack(char c) {
		//���ռ��Ƿ��㹻
		if (_size == _capacity){
			//��ʼ����������Ϊ15
			size_t newC = (_capacity == 0 ? 15 : 2 * _capacity);
			Reserve(newC);
		}
		_str[_size++] = c;
		_str[_size] = '\0';
	}

	//����
	void Reserve(size_t n) {
		if (n > _capacity){
			char *tmp = new char[n + 1];
			strcpy(tmp, _str);
			delete _str;
			//��ָ��ָ���¿ռ�
			_str = tmp;
			//��������
			_capacity = n;
		}
	}

	//βɾ
	void PopBack(){
		if (_size > 0){
			_str[_size--] = '\0';
		}
	}

	//������Ч�ַ��Ĵ�С
	void Resize(size_t n, char c = '\0') {
		if (n > _capacity){
			Reserve(n);
		}

		if (n > _size){
			memset(_str + _size, c, n - _size);
		}
		_size = n;
		_str[_size] = '\0';
	}

	//��ָ��λ��ɾ��Ԫ��,����ָ��ɾ������
	void Erase(size_t pos, size_t len) {
		assert(pos < _size);
		if (pos + len >= _size){
			_size = pos;
			_str[_size] = '\0';
		}
		else{
			//��pos+lenλ�ÿ�ʼŲ�����ݣ�ÿ��������ǰŲ��lenλ��
			for (int i = pos + len; i <= _size; i++){
				_str[pos++] = _str[i];
			}
			_size -= len;
		}
	}

	//׷��
	void Append(const char *str) {
		size_t sz = strlen(str);
		if (_size + sz > _capacity){
			Reserve(_size + sz);
		}
		//��'\0'λ�ÿ�ʼ�����ַ���str
		strcpy(_str + _size, str);
		_size += sz;
	}

	//����һ���ַ�
	void Insertc(size_t pos, char c) {
		//����������Ƿ�����
		//Ԫ��Ų��
		//����size����'\0'
		assert(pos <= _size);
		if (_size == _capacity){
			size_t newCapacity = (_capacity == 0 ? 15 : _capacity * 2);
			Reserve(newCapacity);
		}

		size_t end = _size;
		while (end > pos){
			_str[end] = _str[end - 1];
			end--;
		}
		_size += 1;
		_str[pos] = c;
		_str[_size] = '\0';
	}

	//����һ���ַ���
	void Insertstr(size_t pos, const char *str){
		//����������Ƿ�����
		//Ų��Ԫ��
		//����size,��'\0'
		assert(pos <= _size);
		size_t len = strlen(str);
		//����ʹ�ø�_capacity*2�ķ��������2��֮���ǻ���С��_size+len�ͻ����
		if (_size + len > _capacity){
			Reserve(_size + len);
		}

		size_t end = _size + len;
		while (end > pos + len - 1){
			_str[end] = _str[end - len];
			end--;
		}

		//�����ַ���������ʹ��strcpy()��strcpy(_str+pos, str)
		//���str�е�'\0'һ�𿽱���ȥ��������Ч���ݱ�����
		//strncpy���ԣ�ָ���������ݵĴ�Сstrncpy(_str+pos, str, len)
		while (*str){
			_str[pos++] = *str++;
		}

		_size += len;
	}

	//����һ���ַ�
	size_t find(char c) {
		for (int i = 0; i < _size; i++){
			if (_str[i] == c){
				return i;
			}
		}
		return npos;
	}

	//����һ���ַ���
	size_t find(const char *str, size_t pos = 0){
		const char *posPtr = subStrPos(_str + pos, str);
		if (posPtr){
			return posPtr - _str;
		}

		return npos;
	}

	String& operator+=(char c){
		PushBack(c);
		return *this;
	}

	String& operator+=(const char* str) {
		Append(str);
		return *this;
	}

	String& operator+=(const String& s) {
		*this += s._str;
		return *this;
	}
private:
	char *_str;
	size_t _size;
	size_t _capacity;
public:
	//��̬��Ա�������ʼ��
	static const size_t npos;
};

const size_t String::npos = -1;

String operator+(const String& s1, const String& s2){
	String tmp(s1);
	return tmp + s2;
}

String operator+(const String& s1, const char *str){
	String tmp(s1);
	return tmp + str;
}

String operator+(const String& s1, char c) {
	String tmp(s1);
	return tmp + c;
}

const char* subStrPos(const char *dest, const char *src) {
	const char *dt = dest;
	const char *sc = src;
	while (*dt){
		//�����һ���ַ���ȣ�ƥ��ʣ���ַ�
		if (*dt == *sc){
			const char *mathdest = dt + 1;
			const char *mathsrc = sc + 1;
			//ƥ��ʣ���ַ�
			while (*mathsrc && *mathdest){
				//�����ǰ��ƥ���ַ�����ȣ�ֹͣƥ��
				if (*mathdest != *mathsrc)
					break;
				//�������ƥ��
				mathdest++;
				mathsrc++;
			}

			if (*mathsrc == '\0'){
				//ƥ��ɹ������ص�ǰ�Ӵ���Ŀ���ַ����е���Ԫ�س��ֵ�λ��
				return dt;
			}
		}
		dt++;
	}

	return nullptr;
}