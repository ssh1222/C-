#include <list>
#include <iostream>
using namespace std;

//List节点类
template <class T>
struct ListNode{
	ListNode(const T& val = T()) 
	:_val(val)
	, _next(nullptr)
	, _prev(nullptr)
	{}

	T _val;
	ListNode<T>* _next;
	ListNode<T>* _prev;
};

//List正向迭代器的实现
template <class T,class Ref,class Ptr>
struct ListIterator{
	typedef ListNode<T>* pNode;
	typedef ListIterator<T, Ref, Ptr> Self;

	pNode _node;
	ListInterator(pNode node) 
		:_node(node)
	{}

	//*iterator ---> _node->_data
	Ref operator*(){
		return _node->_data;
	}

	Ptr operator->() {
		return &(_node->_data);
	}

	//++iterator _node->_next
	Self& operator++() {
		_node = _node->_next;
		return *this;
	}

	Self operator++(int) {
		Self tmp(*this);
		_node = _node->_next;
		return tmp;
	}

	bool operator!=(const Self& lit) {
		return _node != lit._node;
	}

	bool operator==(const Self& lit) {
		return _node == lit._node;
	}
};

class Date{
public:
	int _year;
	int _month;
	int _day;
	Date(int year = 1900, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{}
};

//List的实现
template <class T>
class List{
	typedef ListNode<T> Node;
	typedef ListInterator<T, T&, T*> iterator;
	typedef ListInterator<T, const T&, const T*> const_iterator;
	typedef Node* pNode;
public:
	//构造函数
	List(T& val) {
		_head->_val = val;
		_head->_next = _head->_prev = _head;
	}

	//析构函数
	~List(){ 
		if (_head){
			while (_head->_next != _head){
				Node* curNode = _head->_next;
				delete _head->_next;
				_next = curNode->_next;
			}
			delete _head;
			_head = nullptr;
		}
	}

	//插入
	void PushBack(const T& val) {
		pNode newNode = new Node(val);
		pNode prev = _head->_prev;
		prev->_next = newNode;
		newNdoe->_prev = prev;
		newNode->_next = _head;
		_head->_prev = newNode;
	}

	iterator begin() {
		return iterator(_head->_next);
	}

	iterator end() {
		return iterator(_head);
	}

	const_iterator begin() const {
		return const_iterator(_head->_next);
	}

	const_iterator end()const {
		return const_iterator(_head);
	}
private:
	pNode _head;
};

template <class T>
void PrintList(const List<T>& lst) {
	auto lit = lst.begin();
	while (lit != lst.end()){
		cout << *lit << " ";
		++lit;
	}
	cout << endl;
}