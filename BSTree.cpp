#include <iostream>
using namespace std;

template <class T>
struct BSTNode
{
	BSTNode(const T& val = T())
	:_left(nullptr)
	, _right(nullptr)
	, _data(val)
	{}
	BSTNode<T>* _left;
	BSTNode<T>* _right;
	T _data;
};

template <class T>
class BSTree
{
public:
	typedef BSTNode<T> Node;
	BSTree(Node* root = nullptr)
		:_root(root)
	{}

	Node* Copy(Node* root)
	{
		if (root)
		{
			Node* newNode = new Node(root->_data);
			newNode->_left = Copy(root->_left);
			newNode->_right = Copy(root->_right);
			return newNode;
		}
		else
			return nullptr;
		
	}

	BSTree(const BSTree<T>& bst)
	{
		_root = Copy(bst._root);
	}

	BSTree<T>& operator=(const BSTree<T>& bst)
	{
		if (this != &bst)
		{
			if (_root)
			{
				Destory(_root);
			}
			_root = Copy(bst._root);
		}
		return *this;
	}

	void Destory(Node* root)
	{
		if (root)
		{
			Destory(root->_left);
			Destory(root->_right);
			delete root;
			root = nullptr;
		}
	}

	~BSTree()
	{
		if (_root)
			Destory(_root);
	}

	Node* find(const T& x)
	{
		if (_root == nullptr)
			return nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_data == x)
				return cur;
			else if (x > cur->_data)
				cur = cur->_right;
			else
				cur = cur->_left;
		}
		return nullptr;
	}

	bool Insert(const T& x)
	{
		if (_root == nullptr)
		{
			_root = new Node(x);
			return true;
		}

		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_data == x)
				return false;
			else if (x > cur->_data)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				parent = cur;
				cur = cur->_left;
			}
		}
		cur = new Node(x);
		if (parent->_data > x)
			parent->_left = cur;
		else
			parent->_right = cur;
		return true;
	}

	bool Erase(const T& x)
	{
		if (_root == nullptr)
			return false;
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_data == x)
				break;
			else if (cur->_data > x)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				parent = cur;
				cur = cur->_right;
			}
		}

		if (cur == nullptr)
			return false;
		//1. 叶子节点
		if (cur->_left == nullptr && cur->_right == nullptr)
		{
			if (cur != _root)
			{
				if (parent->_left == cur)
					parent->_left = nullptr;
				else
					parent->_right = nullptr;
			}
			else
				_root = nullptr;

			delete cur;
			cur = nullptr;
		}
		//孩子节点不完整
		else if (cur->_left == nullptr)
		{
			if (cur != _root)
			{
				if (parent->_left == cur)
					parent->_left = cur->_right;
				else
					parent->_right = cur->_right;
			}
			else
			{
				_root = cur->_right;
			}
			delete cur;
			cur = nullptr;
		}
		else if (cur->_right == nullptr)
		{
			if (cur != _root)
			{
				if (parent->_right == cur)
					parent->_right = cur->_left;
				else
					parent->_left = cur->_left;
			}
			else
			{
				_root = cur->_left;
			}
			delete cur;
			cur = nullptr;
		}
		else
		{
			Node* leftMost = cur->_left;
			parent = cur;
			//找到左边最大
			while (leftMost->_right)
			{
				parent = leftMost;
				leftMost = leftMost->_right;
			}
			//置换
			cur->_data = leftMost->_data;
			if (parent->_right == leftMost)
				parent->_right = leftMost->_left;
			else
				parent->_left = leftMost->_left;
			//删除节点
			delete leftMost;
			leftMost = nullptr;
		}

		return true;
	}

	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}

	void _Inorder(Node* root)
	{
		if (root)
		{
			_Inorder(root->_left);
			cout << root->_data << " ";
			_Inorder(root->_right);
		}
	}
private:
	Node* _root;
};

int main()
{
	BSTree<int> bstree;
	bstree.Insert(10);
	bstree.Insert(9);
	bstree.Insert(4);
	bstree.Insert(8);
	bstree.Insert(2);
	bstree.Insert(19);
	bstree.Insert(31);
	
	bstree.Inorder();
	
	BSTree<int> copy(bstree);
	copy.Inorder();
	copy.Erase(10);
	copy.Inorder();
	copy = bstree;
	copy.Inorder();
	
	return 0;
}