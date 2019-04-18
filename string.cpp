#include <iostream>
#include <assert.h>
using namespace std;

class String{
public:
	typedef char* iterator;
	typedef const char* const_iterator;
	//构造函数
	String(char *str = ""){
		assert(str != nullptr);
		//_size:有效字符数量，不包含'\0'
		_size = strlen(str);
		_str = new char[_size + 1];
		strcpy(_str, str);//while(*str1++ = *str2++);
		_capacity = _size;
	}
	//拷贝构造
	String(const String& s) 
		:_str(nullptr)
		, _size(0)
		, _capacity(0)
	{
		String tmp(s._str);
		Swap(tmp);
	}

	//交换函数
	void Swap(String& s) {
		swap(_str, s._str);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}

	//赋值运算符重载
	String& operator=(String s){
		Swap(s);
		return *this;
	}

	//[]形式访问字符,可读可改
	char& operator[](size_t pos) {
		assert(pos < _size);
		return _str[pos];
	}

	//[]只读，不可改
	const char& operator[](size_t pos) const {
		assert(pos < _size);
		return _str[pos];
	}

	//迭代器的使用
	//返回begin位置，可读可写
	iterator begin() {
		return _str;
	}

	//返回end的位置，可读可写
	iterator end() {
		return _str + _size;
	}

	//返回begin位置，只读
	const_iterator begin()const {
		return _str;
	}

	//返回end位置，只读
	const_iterator end()const {
		return _str + _size;
	}

	//析构函数
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

	//在尾部插入
	void PushBack(char c) {
		//检查空间是否足够
		if (_size == _capacity){
			//初始化容量设置为15
			size_t newC = (_capacity == 0 ? 15 : 2 * _capacity);
			Reserve(newC);
		}
		_str[_size++] = c;
		_str[_size] = '\0';
	}

	//扩容
	void Reserve(size_t n) {
		if (n > _capacity){
			char *tmp = new char[n + 1];
			strcpy(tmp, _str);
			delete _str;
			//让指针指向新空间
			_str = tmp;
			//更新容量
			_capacity = n;
		}
	}

	//尾删
	void PopBack(){
		if (_size > 0){
			_str[_size--] = '\0';
		}
	}

	//设置有效字符的大小
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

	//从指定位置删除元素,可以指定删除长度
	void Erase(size_t pos, size_t len) {
		assert(pos < _size);
		if (pos + len >= _size){
			_size = pos;
			_str[_size] = '\0';
		}
		else{
			//从pos+len位置开始挪动数据，每个数据向前挪动len位置
			for (int i = pos + len; i <= _size; i++){
				_str[pos++] = _str[i];
			}
			_size -= len;
		}
	}

	//追加
	void Append(const char *str) {
		size_t sz = strlen(str);
		if (_size + sz > _capacity){
			Reserve(_size + sz);
		}
		//从'\0'位置开始插入字符串str
		strcpy(_str + _size, str);
		_size += sz;
	}

	//插入一个字符
	void Insertc(size_t pos, char c) {
		//检查容量：是否增容
		//元素挪动
		//更新size，补'\0'
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

	//插入一个字符串
	void Insertstr(size_t pos, const char *str){
		//检查容量：是否增容
		//挪动元素
		//更新size,补'\0'
		assert(pos <= _size);
		size_t len = strlen(str);
		//不能使用给_capacity*2的方法，如果2倍之后还是还是小于_size+len就会出错
		if (_size + len > _capacity){
			Reserve(_size + len);
		}

		size_t end = _size + len;
		while (end > pos + len - 1){
			_str[end] = _str[end - len];
			end--;
		}

		//插入字符串，不能使用strcpy()，strcpy(_str+pos, str)
		//会把str中的'\0'一起拷贝过去，导致有效内容被覆盖
		//strncpy可以，指定拷贝内容的大小strncpy(_str+pos, str, len)
		while (*str){
			_str[pos++] = *str++;
		}

		_size += len;
	}

	//查找一个字符
	size_t find(char c) {
		for (int i = 0; i < _size; i++){
			if (_str[i] == c){
				return i;
			}
		}
		return npos;
	}

	//查找一个字符串
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
	//静态成员在类外初始化
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
		//如果第一个字符相等，匹配剩余字符
		if (*dt == *sc){
			const char *mathdest = dt + 1;
			const char *mathsrc = sc + 1;
			//匹配剩余字符
			while (*mathsrc && *mathdest){
				//如果当前带匹配字符不相等，停止匹配
				if (*mathdest != *mathsrc)
					break;
				//继续向后匹配
				mathdest++;
				mathsrc++;
			}

			if (*mathsrc == '\0'){
				//匹配成功，返回当前子串在目标字符串中的首元素出现的位置
				return dt;
			}
		}
		dt++;
	}

	return nullptr;
}