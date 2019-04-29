#include <iostream>
#include <list>
#include <queue>
#include <stdlib.h>
using namespace std;

template <class T, class Container>
class Queue{
public:
	T& Front(){
		return _con.front();
	}

	void Push(const T& val){
		_con.push_back(val);
	}

	void Pop() {
		_con.pop_front();
	}

	T& Back() {
		return _con.back();
	}

	size_t Size() {
		return _con.size();
	}

	bool Empty() {
		return _con.empty();
	}
private:
	Container _con;
};

//返回较大的
template <class T>
class Greater{
public:
	//'()'运算符重载函数
	bool operator()(const T& a, const T& b) {
		return a > b;
	}
};

//返回较小的
template <class T>
class Less{
public:
	//'()'运算符重载函数
	bool operator()(const T& a, const T& b) {
		return a < b;
	}
};

template <class T, class Container, class Compare>
class Priority_Queue{
public:
	void Push(const T& val){
		_con.push_back(val);
		//向上调整
		shiftUp(_con.size() - 1);
	}
	void shiftUp(size_t child) {
		size_t parent = (child - 1) / 2;
		while (child > 0){
			if (_con[child] > _con[parent]){
				swap(_con[child], _con[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}else
				break;
		}
	}
	void Pop() {
		swap(_con[0], _con[_con.size() - 1]);
		_con.pop_back();
		//向下调整
		shiftDown(0);
	}

	void shiftDown(size_t parent) {
		size_t child = 2 * parent + 1;

		while (child < _con.size()){
			if (child + 1 < _con.size() && _con[child + 1] > _con[child])
				++child;
			if (_con[child] > _con[parent]){
				swap(_con[child], _con[parent]);
				parent = child;
				child = 2 * parent + 1;
			}else
				break;
		}
	}

	T& Top() {
		return _con.front();
	}

	size_t Size() {
		return _con.size();
	}

	bool Empty() {
		return _con.empty();
	}
private:
	Container _con;
	Compare _com;
};

int main() {
	Priority_Queue<int, vector<int>,Less<int>> pq;
	pq.Push(1);
	pq.Push(2);
	pq.Push(100);
	pq.Push(20);
	pq.Push(6);

	while (!pq.Empty()){
		cout << pq.Top() << " ";
		pq.Pop();
	}
	cout << endl;
	system("pause");
	return 0;
}