#include <iostream>
#include <list>

using namespace std;

template<class KeyType>
struct  RBTreeNode
{
	KeyType key;
	int value;
	bool color;
	RBTreeNode<KeyType>* left;
	RBTreeNode<KeyType>* right;
	RBTreeNode<KeyType>* parent;
	RBTreeNode(KeyType key, int value, bool color, RBTreeNode* parent, RBTreeNode* left, RBTreeNode* right) :
		key(key), value(value), color(color), parent(parent), left(left), right(right) {};
};

template<class T>
class  RBTree
{
public:
	RBTree();
	~RBTree();

	void insert(T key, int value);
	void remove(T key);
	RBTreeNode<T>* find(T key);
	void print();
	void clear();
	void get_values(list<T>& valueList); 
	void get_keys(list<T>& keyList);
	bool is_empty();


private:
	void left_rotate(RBTreeNode<T>*& root, RBTreeNode<T>* x);
	void right_rotate(RBTreeNode<T>*& root, RBTreeNode<T>* y);

	void insert(RBTreeNode<T>*& root, RBTreeNode<T>* node);
	void insert_fix(RBTreeNode<T>*& root, RBTreeNode<T>* node);
	void clear(RBTreeNode<T>*& node);

	void remove(RBTreeNode<T>*& root, RBTreeNode<T>* node);
	void remove_fix(RBTreeNode<T>*& root, RBTreeNode<T>* node, RBTreeNode<T>* parent);

	RBTreeNode<T>* find(RBTreeNode<T>* node, T key) const;
	void print(RBTreeNode<T>* node)const;
	void get_values(RBTreeNode<T>* tree, list<T>& valueList);
	void get_keys(RBTreeNode<T>* tree, list<T>& keyList);
private:
	RBTreeNode<T>* root;
};

template<class T>	
RBTree<T>::RBTree() :root(NULL) {
	root = nullptr;
}

template<class T>		
RBTree<T>::~RBTree() {
	clear(root);
}

template<class T>
bool RBTree<T>::is_empty()
{
	return (root == nullptr) ? true : false;
}

template<class T>
void RBTree<T>::clear() {
	clear(root);
}

template<class T>	
void RBTree<T>::left_rotate(RBTreeNode<T>*& root, RBTreeNode<T>* x) {
	RBTreeNode<T>* y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == NULL)
		root = y;
	else {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
};

template<class T>		
void RBTree<T>::right_rotate(RBTreeNode<T>*& root, RBTreeNode<T>* y) {
	RBTreeNode<T>* x = y->left;
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == NULL)
		root = x;
	else {
		if (y == y->parent->right)
			y->parent->right = x;
		else
			y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
};

template<class T>		
void RBTree<T>::insert(T key, int value)
{
	RBTreeNode<T>* z = new RBTreeNode<T>(key, value, 1, NULL, NULL, NULL);
	insert(root, z);
};

template<class T>
void RBTree<T>::insert(RBTreeNode<T>*& root, RBTreeNode<T>* node)
{
	RBTreeNode<T>* x = root;
	RBTreeNode<T>* y = NULL;
	while (x != NULL)
	{
		y = x;
		if (node->key > x->key)
			x = x->right;
		else
			x = x->left;
	}
	node->parent = y;
	if (y != NULL)
	{
		if (node->key > y->key)
			y->right = node;
		else
			y->left = node;
	}
	else
		root = node;
	node->color = 1;
	insert_fix(root, node);
};

template<class T>
void RBTree<T>::insert_fix(RBTreeNode<T>*& root, RBTreeNode<T>* node)
{
	RBTreeNode<T>* parent;
	parent = node->parent;
	while (node != RBTree::root && parent->color == 1)
	{
		RBTreeNode<T>* gparent = parent->parent;
		if (gparent->left == parent)
		{
			RBTreeNode<T>* uncle = gparent->right;
			if (uncle != NULL && uncle->color == 1)
			{
				parent->color = 0;
				uncle->color = 0;
				gparent->color = 1;
				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->right == node)
				{
					left_rotate(root, parent);
					swap(node, parent);
				}
				right_rotate(root, gparent);
				gparent->color = 1;
				parent->color = 0;
				break;
			}
		}
		else
		{
			RBTreeNode<T>* uncle = gparent->left;
			if (uncle != NULL && uncle->color == 1)
			{
				gparent->color = 1;
				parent->color = 0;
				uncle->color = 0;

				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->left == node)
				{
					right_rotate(root, parent);
					swap(parent, node);
				}
				left_rotate(root, gparent);
				parent->color = 0;
				gparent->color = 1;
				break;
			}
		}
	}
	root->color = 0;
}

template<class T>
void RBTree<T>::clear(RBTreeNode<T>*& node)
{
	if (node == NULL)
		return;
	clear(node->left);
	clear(node->right);
	delete node;
	node = nullptr;
}

template<class T>
void RBTree<T>::remove(T key)
{
	RBTreeNode<T>* deletenode = find(root, key);
	if (deletenode != NULL)
		remove(root, deletenode);
}

template<class T>
void RBTree<T>::remove(RBTreeNode<T>*& root, RBTreeNode<T>* node)
{
	RBTreeNode<T>* child, * parent;
	bool color;
	if (node->left != NULL && node->right != NULL)
	{
		RBTreeNode<T>* replace = node;
		replace = node->right;
		while (replace->left != NULL)
		{
			replace = replace->left;
		}
		if (node->parent != NULL)
		{
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		else
			root = replace;
		child = replace->right;
		parent = replace->parent;
		color = replace->color;
		if (parent == node)
			parent = replace;
		else
		{
			if (child != NULL)
				child->parent = parent;
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}
		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;
		if (color == 0)
			remove_fix(root, child, parent);

		delete node;
		return;
	}
	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;
	if (child)
	{
		child->parent = parent;
	}
	if (parent)
	{
		if (node == parent->left)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		RBTree::root = child;

	if (color == 0)
	{
		remove_fix(root, child, parent);
	}
	delete node;

}

template<class T>
void RBTree<T>::remove_fix(RBTreeNode<T>*& root, RBTreeNode<T>* node, RBTreeNode<T>* parent)
{
	RBTreeNode<T>* othernode;
	while ((!node) || node->color == 0 && node != RBTree::root)
	{
		if (parent->left == node)
		{
			othernode = parent->right;
			if (othernode->color == 1)
			{
				othernode->color = 0;
				parent->color = 1;
				left_rotate(root, parent);
				othernode = parent->right;
			}
			else
			{
				if (!(othernode->right) || othernode->right->color == 0)
				{
					othernode->left->color = 0;
					othernode->color = 1;
					right_rotate(root, othernode);
					othernode = parent->right;
				}
				othernode->color = parent->color;
				parent->color = 0;
				othernode->right->color = 0;
				left_rotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			othernode = parent->left;
			if (othernode->color == 1)
			{
				othernode->color = 0;
				parent->color = 1;
				right_rotate(root, parent);
				othernode = parent->left;
			}
			if ((!othernode->left || othernode->left->color == 0) && (!othernode->right || othernode->right->color == 0))
			{
				othernode->color = 1;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!(othernode->left) || othernode->left->color == 0)
				{
					othernode->right->color = 0;
					othernode->color = 1;
					left_rotate(root, othernode);
					othernode = parent->left;
				}
				othernode->color = parent->color;
				parent->color = 0;
				othernode->left->color = 0;
				right_rotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		node->color = 0;
}

template<class T>
RBTreeNode<T>* RBTree<T>::find(T key)
{
	return find(root, key);
}

template<class T>
RBTreeNode<T>* RBTree<T>::find(RBTreeNode<T>* node, T key) const
{
	if (node == NULL || node->key == key)
		return node;
	else
		if (key > node->key)
			return find(node->right, key);
		else
			return find(node->left, key);
}

template<class T>
void RBTree<T>::print() {
	if (root == NULL)
		cout << "empty RBtree\n";
	else
		print(root);
}

template<class T>
void RBTree<T>::print(RBTreeNode<T>* node)const {
	if (node) {
		cout << node->value << " ";
		print(node->left);
		print(node->right);	
	}
}

template<class T>
void RBTree<T>::get_values(list<T>& valueList) {
	if (root == NULL)
		cout << "empty RBtree\n";
	else
		get_values(root, valueList);
};

template<class T>
void RBTree<T>::get_values(RBTreeNode<T>* tree, list<T>& valueList) {
	if (tree != NULL) {
		valueList.push_back(tree->value);
		get_values(tree->left, valueList);
		get_values(tree->right, valueList);
	}
}

template<class T>
void RBTree<T>::get_keys(list<T>& keyList) {
	if (root == NULL)
		cout << "empty RBtree\n";
	else
		get_keys(root, keyList);
};

template<class T>
void RBTree<T>::get_keys(RBTreeNode<T>* tree, list<T>& keyList) {
	if (tree != NULL) {
		keyList.push_back(tree->key);
		get_keys(tree->left, keyList);
		get_keys(tree->right, keyList);
	}
}