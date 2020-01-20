template<class K>
struct BSTreeNode
{
	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;
	K _key;

	BSTreeNode(const K& key)
		: _key(key)
		, _left(nullptr)
		, _right(nullptr)
	{}
};

template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node;//在这个作用域里，直接用Node就行
public:
	BSTree()
		:_root(nullptr)
	{

	}

	~BSTree()
	{
		//...
	}
	//尽可能不要拷贝构造，拷贝一个树代价太大

	bool Insert(const K& key)
	{//不是push，push这样的接口是用在线性的容器上的
		if (_root == nullptr)
		{
			_root = new Node(key);//int转换成Node时的错误，没写构造函数，new的时候会调Node的构造函数，认为是int转换成Node
			return  true;
		}

		Node* cur = _root;//cur只是临时结点
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{//二叉搜索树不允许相等值
				return false;
			}
		}
		cur = new Node(key);//此时并未真正 链接上
		if (parent->_key < key)
		{
			parent->_right = cur;
		}
		else if (parent->_key > key)
		{
			parent->_left = cur;
		}
		return true;
	}


	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;
	}

	bool Erase(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{//先找到结点和他的parent
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{//erase的实现分三种情况，叶子结点、一个孩子的结点、两个孩子的结点 ==> 左为空，右为空，左右都不为空
				Node* del = cur;//注意del的定义位置，在这个else的最开始，而不是在下面左右都不为空的else里
				if (cur->_left == nullptr)
				{
					if (parent==nullptr)//这种情况是（要删结点左为空或者右为空时）：即要删除根节点，parent为空,防止程序崩溃，做出判断
					{
						_root = cur->_right;
					}
					else
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_right;
						}
						else if (parent->_right == cur)
						{
							parent->_right = cur->_right;
						}
					}
				}
				else if (cur->_right == nullptr)
				{
					if (parent == nullptr)//这种情况是（要删结点左为空或者右为空时）：即要删除根节点，parent为空,防止程序崩溃，做出判断
					{
						_root = cur->_left;
					}
					else
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
					}
				}
				else
				{//左右都不为空，找替代结点
					Node* lessParent = cur;//parent不能给空，体会循环没进去的情况，即一步就找到了lessRight
					Node* lessRight = cur->_right;//右树的最小
					while (lessRight->_left)//找右边的最小结点
					{
						lessParent = lessRight;
						lessRight = lessRight->_left;
					}
					cur->_key = lessRight->_key;
					del = lessRight;//这种情况删除的不是cur，而是lessright

					if (lessParent->_left == lessRight)//要删结点是父亲左孩子
					{
						lessParent->_left = lessRight->_right;//rightLess->_right肯定是没有的，因为当前节点已经是最小的
					}
					else
					{//要删结点是父亲右孩子
						lessParent->_right = lessRight->_right;
					}
				}

				delete del;
				return true;
			}
		}
		return false;
	}


	bool _InsertR(Node*& root, const K& key)//注意引用，不加引用的话没有连接的过程，注意新结点要作为父亲某一指针的别名，不仅仅是赋值给newnode
	{
		if (root == nullptr)
		{
			root == new Node(key);
		}

		if (root->_key > key)
		{
			_InsertR(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _InsertR(root->_right, key);
		}
		else
		{//相等的话不能插入
			return false;
		}
	}

	//递归实现Insert
	bool InsertR(const K& key)
	{
		_InsertR(_root, key);
	}

	Node* _FindR(Node* root, const K& key)
	{
		if (root == nullptr)
			return nullptr;

		if (root->_key == key)
		{
			return root;
		}
		else if (root->_key < key)
		{
			return _FindR(root->_right,key);
		}
		else if (root->_key > key)
		{
			return _FindR(root->_left, key);
		}
	}
	Node* FindR(const K& key)
	{//递归要显式传根进来，而*this是隐式传入，所以要封装一层
		_FindR(_root, key);
	}

	bool EraseR(const K& key)
	{
		//...
	}

	//注意中序遍历的写法是封装了一层的
	void InOrder()
	{//根节点是隐含传进来的(this指针)
		_InOrder(_root);//根是私有的，要到类里面去拿，所以要封装一层
		cout << endl;
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

private:
	Node* _root;
};

void TestBSTree()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int> t;
	for (auto e : a)
	{
		t.Insert(e);
	}
	//测试顺序根据代码逻辑设置=>白盒测试
	t.InOrder();
	t.Erase(2);
	t.Erase(8);
	t.Erase(1);
	t.Erase(7);
	t.Erase(5);

	t.InOrder();
}