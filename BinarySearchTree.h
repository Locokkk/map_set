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
	typedef BSTreeNode<K> Node;//������������ֱ����Node����
public:
	BSTree()
		:_root(nullptr)
	{

	}

	~BSTree()
	{
		//...
	}
	//�����ܲ�Ҫ�������죬����һ��������̫��

	bool Insert(const K& key)
	{//����push��push�����Ľӿ����������Ե������ϵ�
		if (_root == nullptr)
		{
			_root = new Node(key);//intת����Nodeʱ�Ĵ���ûд���캯����new��ʱ����Node�Ĺ��캯������Ϊ��intת����Node
			return  true;
		}

		Node* cur = _root;//curֻ����ʱ���
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
			{//�������������������ֵ
				return false;
			}
		}
		cur = new Node(key);//��ʱ��δ���� ������
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
		{//���ҵ���������parent
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
			{//erase��ʵ�ַ����������Ҷ�ӽ�㡢һ�����ӵĽ�㡢�������ӵĽ�� ==> ��Ϊ�գ���Ϊ�գ����Ҷ���Ϊ��
				Node* del = cur;//ע��del�Ķ���λ�ã������else���ʼ�����������������Ҷ���Ϊ�յ�else��
				if (cur->_left == nullptr)
				{
					if (parent==nullptr)//��������ǣ�Ҫɾ�����Ϊ�ջ�����Ϊ��ʱ������Ҫɾ�����ڵ㣬parentΪ��,��ֹ��������������ж�
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
					if (parent == nullptr)//��������ǣ�Ҫɾ�����Ϊ�ջ�����Ϊ��ʱ������Ҫɾ�����ڵ㣬parentΪ��,��ֹ��������������ж�
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
				{//���Ҷ���Ϊ�գ���������
					Node* lessParent = cur;//parent���ܸ��գ����ѭ��û��ȥ���������һ�����ҵ���lessRight
					Node* lessRight = cur->_right;//��������С
					while (lessRight->_left)//���ұߵ���С���
					{
						lessParent = lessRight;
						lessRight = lessRight->_left;
					}
					cur->_key = lessRight->_key;
					del = lessRight;//�������ɾ���Ĳ���cur������lessright

					if (lessParent->_left == lessRight)//Ҫɾ����Ǹ�������
					{
						lessParent->_left = lessRight->_right;//rightLess->_right�϶���û�еģ���Ϊ��ǰ�ڵ��Ѿ�����С��
					}
					else
					{//Ҫɾ����Ǹ����Һ���
						lessParent->_right = lessRight->_right;
					}
				}

				delete del;
				return true;
			}
		}
		return false;
	}


	bool _InsertR(Node*& root, const K& key)//ע�����ã��������õĻ�û�����ӵĹ��̣�ע���½��Ҫ��Ϊ����ĳһָ��ı������������Ǹ�ֵ��newnode
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
		{//��ȵĻ����ܲ���
			return false;
		}
	}

	//�ݹ�ʵ��Insert
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
	{//�ݹ�Ҫ��ʽ������������*this����ʽ���룬����Ҫ��װһ��
		_FindR(_root, key);
	}

	bool EraseR(const K& key)
	{
		//...
	}

	//ע�����������д���Ƿ�װ��һ���
	void InOrder()
	{//���ڵ���������������(thisָ��)
		_InOrder(_root);//����˽�еģ�Ҫ��������ȥ�ã�����Ҫ��װһ��
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
	//����˳����ݴ����߼�����=>�׺в���
	t.InOrder();
	t.Erase(2);
	t.Erase(8);
	t.Erase(1);
	t.Erase(7);
	t.Erase(5);

	t.InOrder();
}