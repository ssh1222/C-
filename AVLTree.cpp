
template <class T>
struct AVLNode
{
	AVLNode(const T& val = T())
	:_left(nullptr)
	, _right(nullptr)
	, _parent(nullptr)
	, _data(val)
	, _bf(0)
	{}
	AVLNode<T>* _left;
	AVLNode<T>* _right;
	AVLNode<T>* _parent;
	
	T _data;
	int _bf;
};

template <class T>
class AVLTree
{
public:
	typedef AVLNode<T> Node;

	bool Insert(const T& val)
	{
		if (_root == nullptr)
		{
			_root = new Node(val);
			return true;
		}

		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (val > cur->_data)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (val < cur->_data)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return false;
		}

		cur = new Node(val);
		if (parent->_data > cur->_data)
			parent->_left = cur;
		else
			parent->_right = cur;
		cur->_parent = parent;

		//调平衡
		while (parent)
		{
			//更新平衡因子
			if (parent->_left == cur)
				--parent->_bf;
			else
				++parent->_bf;
			if (parent->_bf == 0)
				break;
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				//继续向上更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2)
			{
				//旋转
				if (parent->_bf == -2 && cur->_bf == -1)
				{
					//右旋
				}
			}
		}

	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//单向链接 subL , parent, subLR
		subL->_right = parent;
		parent->_left = subLR;

		//向上链接subLR
		if (subLR)
			subLR->_parent = parent;
		
		//subL，parent->parent 双向链接
		if (parent != _root)
		{
			Node* gParent = parent->_parent;
			if (gParent->_left == parent)
				gParent->_left = subL;
			else
				gParent->_right = subL;
			subL->_parent = gParent;
		}
		else
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		

		//向上链接parent, subL
		parent->_parent = subL;

		//更新平衡因子
		subL->_bf = parent->_bf = 0;
	}

private:
	Node* _root = nullptr;
};