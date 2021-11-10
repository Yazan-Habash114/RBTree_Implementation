#include <iostream>

using namespace std;

#define BLACK 0
#define RED 1

struct node {
	int key;
	bool colour;
	node* parent, * right, * left;
};

node* create_node(int key) {
	node* n = new node;
	n->key = key;
	n->colour = RED; // Default colour = red
	n->parent = n->left = n->right = NULL;
	return n;
}

node* BSTInsert(node* root, node* pt)
{
	/* If the tree is empty, return a new node */
	if (root == NULL)
		return pt;

	/* Otherwise, recur down the tree */
	if (pt->key <= root->key) {
		root->left = BSTInsert(root->left, pt);
		root->left->parent = root;
	}
	else if (pt->key > root->key) {
		root->right = BSTInsert(root->right, pt);
		root->right->parent = root;
	}

	/* return the (unchanged) node pointer */
	return root;
}

void left_rotate(node*& root, node*& here) {
	node* y = here->right;
	if (y != NULL) {
		here->right = y->left;
		if (y->left != NULL)
			y->left->parent = here;
		y->parent = here->parent;
		if (here->parent == NULL)
			root = y;
		else if (here == here->parent->left)
			here->parent->left = y;
		else
			here->parent->right = y;
		y->left = here;
		here->parent = y;
	}
}

void right_rotate(node*& root, node*& here) {
	node* y = here->left;
	if (y != NULL) {
		here->left = y->right;
		if (y->left != NULL)
			y->left->parent = here;
		y->parent = here->parent;
		if (here->parent == NULL)
			root = y;
		else if (here == here->parent->left)
			here->parent->left = y;
		else
			here->parent->right = y;
		y->right = here;
		here->parent = y;
	}
}

void fix_violation(node*& root, node*& here) {
	node* parent_here = NULL;
	node* grand_here = NULL;

	while ((here != root) && (here->colour != BLACK) && (here->parent->colour == RED)) {
		parent_here = here->parent;
		grand_here = here->parent->parent;

		// Case A: parenet of here is left child of grand-parenet of here
		if (parent_here == grand_here->left) {
			node* uncle = grand_here->right;
			// Case 1: The uncle of here is red
			if (uncle != NULL && uncle->colour == RED) {
				grand_here->colour = RED;
				parent_here->colour = BLACK;
				uncle->colour = BLACK;
				here = grand_here;
			}
			else {
				// Case 2: here is right child of parent ==> left rotation
				if (here == parent_here->right) {
					left_rotate(root, parent_here);
					here = parent_here;
					parent_here = here->parent;
				}
				// Automatically go to case 3
				// here is left child of parent ==> right_rotation
				right_rotate(root, grand_here);
				swap(parent_here->colour, grand_here->colour);
				here = parent_here;
			}
		}

		/* Case : B
		   Parent of pt is right child
		   of Grand-parent of pt */
		else
		{
			node* uncle = grand_here->left;

			/*  Case : 1
				The uncle of pt is also red
				Only Recoloring required */
			if (uncle != NULL && uncle->colour == RED) {
				grand_here->colour = RED;
				parent_here->colour = BLACK;
				uncle->colour = BLACK;
				here = grand_here;
			}
			else {
				/* Case : 2
				   pt is left child of its parent
				   Right-rotation required */
				if (here == parent_here->left) {
					right_rotate(root, parent_here);
					here = parent_here;
					parent_here = here->parent;
				}

				/* Case : 3
				   pt is right child of its parent
				   Left-rotation required */
				left_rotate(root, grand_here);
				swap(parent_here->colour, grand_here->colour);
				here = parent_here;
			}
		}
	}
	root->colour = BLACK;
}

void insert(node*& root, node* n) {
	root = BSTInsert(root, n);
	fix_violation(root, n);
}

bool search(node* root, int key) {
	if (root == NULL)
		return false;
	if (root->key == key)
		return true;
	return key < root->key ? search(root->left, key) : search(root->right, key);
}

void print(node* root) { // Pre-Order printing
	if (root == NULL)
		return;
	cout << root->key << "(";
	bool col = root->colour;
	if (col)
		cout << "RED)_";
	else
		cout << "BLACK)_";
	print(root->left);
	print(root->right);
}

node* select(node* root, int key) {
	if (root == NULL)
		return NULL;
	if (root->key == key)
		return root;
	return key <= root->key ? select(root->left, key) : select(root->right, key);
}

int main(void) {
	node* root = NULL;
	insert(root, create_node(4));
	insert(root, create_node(5));
	insert(root, create_node(2));
	insert(root, create_node(9));
	insert(root, create_node(16));
	insert(root, create_node(7));
	insert(root, create_node(1));
	insert(root, create_node(19));
	insert(root, create_node(14));
	insert(root, create_node(11));
	insert(root, create_node(21));
	insert(root, create_node(13));
	insert(root, create_node(0));

	print(root);
	cout << endl;
	
	system("pause");
	return 0;
}