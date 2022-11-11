#include <iostream>
using namespace std;

/* Node of AVL tree */
struct Node {
	int key;
	Node* left;
	Node* right;
	int height;
};

/* Function to get the height of the tree */
int height(Node* N) {
	if (N == NULL)
		return 0;
	return N->height;
}

/* Update height of node */
void update_height(Node* node) {
	node->height = max(height(node->left), height(node->right)) + 1;
}

/* Create node */
void createNode(int key, Node*& node) {
	node = new Node;
	if (node) {
		node->key = key;
		node->left = node->right = NULL;
		node->height = 1;
	}
}

/* Right rotation */
Node* right_rotate(Node* imbalance) {
	Node* l_imb = imbalance->left;
	Node* right_l_imb = l_imb->right;

	// Perform rotation
	l_imb->right = imbalance;
	imbalance->left = right_l_imb;

	// Update height
	update_height(l_imb);
	update_height(imbalance);

	// Return new root
	return l_imb;
}

/* Left rotation */
Node* left_rotate(Node* imbalance) {
	Node* r_imb = imbalance->right;
	Node* left_r_imb = r_imb->left;

	// Perform rotation
	r_imb->left = imbalance;
	imbalance->right = left_r_imb;

	// Update height
	update_height(r_imb);
	update_height(imbalance);

	// Return new root
	return r_imb;
}

/* Get balance factor of node */
int get_balance(Node* node) {
	if (node == NULL)
		return 0;
	return height(node->left) - height(node->right);
}

/* Rebalance tree */
void rebalance(Node*& root, int key) {
	int balance = 0;
	if (root != NULL) {
		update_height(root); // Cap nhat chieu cao cho node
		balance = get_balance(root); // Chi so can bang tai node 
	}

	// Left Left case
	if (balance > 1 && key < root->left->key)
		root = right_rotate(root);
	// Left Right case
	if (balance > 1 && key > root->left->key) {
		root->left = left_rotate(root->left);
		root = right_rotate(root);
	}
	// Right Right case
	if (balance < -1 && key > root->right->key)
		root = left_rotate(root);
	// Right Left case
	if (balance < -1 && key < root->right->key) {
		root->right = right_rotate(root->right);
		root = left_rotate(root);
	}
}

/* Insert node in an AVL tree */
void insertNode(Node*& root, Node* node) {
	if (root == NULL)
		root = node;
	else if (node->key < root->key)
		insertNode(root->left, node);
	else if (node->key > root->key)
		insertNode(root->right, node);
	else return;

	update_height(root); // Cap nhat chieu cao cho node
	int balance = get_balance(root); // Chi so can bang tai node 

	// Left Left case
	if (balance > 1 && node->key < root->left->key)
		root = right_rotate(root);
	// Left Right case
	if (balance > 1 && node->key > root->left->key) {
		root->left = left_rotate(root->left);
		root = right_rotate(root);
	}
	// Right Right case
	if (balance < -1 && node->key > root->right->key)
		root = left_rotate(root);
	// Right Left case
	if (balance < -1 && node->key < root->right->key) {
		root->right = right_rotate(root->right);
		root = left_rotate(root);
	}
}

/* Find min-node of the right subtree of delnode */
void minNode(Node* node, Node*& minnode) {
	if (node->left == NULL)
		minnode = node;
	minNode(node->left, minnode);
}

/* Delete node */
void deleteNode(Node*& root, int delnode) {
	if (root == NULL)
		cout << "\nKhong tim thay node can xoa\n";
	else if (delnode < root->key)
		deleteNode(root->left, delnode);
	else if (delnode > root->key)
		deleteNode(root->right, delnode);
	else {
		if (root->left == NULL && root->right == NULL)
			root = NULL;
		else if (root->left == NULL) {
			root = root->right;
			delete root;
		}
		else if (root->right == NULL) {
			root = root->left;
			delete root;
		}
		else {
			Node* minnode = NULL;
			minNode(root->right, minnode);
			root->key = minnode->key;
			deleteNode(minnode, delnode);
		}
	}
	rebalance(root, delnode);
}

/* Print node */
void print_node(int key, int height) {
	for (int i = 0; i < height; i++)
		cout << "  ";
	cout << key << endl;
}

/* Print tree */
void print_tree(Node* root, int height) {
	if (root == NULL) {
		for (int i = 0; i < height; i++)
			cout << "  ";
		cout << "*" << endl;
		return;
	}
	print_tree(root->right, height + 1);
	print_node(root->key, height);
	print_tree(root->left, height + 1);
}
int main() {

	// Create AVL Tree
	Node* root = NULL; 

	// Insert node 
	int size, i = 1;
	cout << "\nNhap so luong node: "; cin >> size;
	while (i <= size) {
		int key;
		Node* node = NULL;
		cout << "\nNhap node thu " << i << ": ";
		cin >> key;
		createNode(key, node);
		insertNode(root, node);
		i++;
	}

	// Print AVL tree
	cout << "\nCay AVL vua nhap\n";
	print_tree(root, 0);
	
	// Delete node
	int delnode;
	cout << "\nNhap gia tri node can xoa: ";
	cin >> delnode;
	deleteNode(root, delnode);

	cout << "\nCay AVL sau khi xoa\n";
	print_tree(root, 0);
}