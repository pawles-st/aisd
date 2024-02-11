#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class BST {
	public:
	
	BST() : root(nullptr) {}

	void insert(long long int k, long long int *comparisons, long long int *read_ptr, long long int *write_ptr) {
		Node *y = nullptr;
		*read_ptr += 1;
		Node *x = this->root;

		while (x != nullptr) {
			y = x;
			*comparisons += 1;
			if (k < x->value) {
				*read_ptr += 1;
				x = x->left;
			} else {
				*read_ptr += 1;
				x = x->right;
			}
		}

		Node *new_node = new Node(k);
		*write_ptr += 1;
		new_node->parent = y;

		if (y == nullptr) {
			*write_ptr += 1;
			this->root = new_node;
		} else if (k < y->value) {
			*comparisons += 1;
			*write_ptr += 1;
			y->left = new_node;
		} else {
			*comparisons += 1;
			*write_ptr += 1;
			y->right = new_node;
		}
	}

	bool del(long long int k, long long int *comparisons, long long int *read_ptr, long long int *write_ptr) {

		Node *z = search(k, comparisons, read_ptr, write_ptr);

		if (z == nullptr) {

			return false;

		} else {

			if (z->left == nullptr) {

				*read_ptr += 2;
				transplant(z, z->right, comparisons, read_ptr, write_ptr);

			} else if (z->right == nullptr) {

				*read_ptr += 3;
				transplant(z, z->left, comparisons, read_ptr, write_ptr);

			} else {

				*read_ptr += 3;
				Node *y = minimum(z->right, comparisons, read_ptr, write_ptr);

				*read_ptr += 1;
				if (y->parent != z) {

					*read_ptr += 1;
					transplant(y, y->right, comparisons, read_ptr, write_ptr);

					*read_ptr += 2;
					*write_ptr += 2;
					y->right = z->right;
					y->right->parent = y;

				}

				transplant(z, y, comparisons, read_ptr, write_ptr);

				*read_ptr += 2;
				*write_ptr += 2;
				y->left = z->left;
				y->left->parent = y;
			}

			delete z;
			
			return true;
		}
	}

	long long int height() {
		if (this->root == nullptr) {
			return -1;
		} else {
			return height(this->root);
		}
	}

	private:

	struct Node {
		long long int value;
		Node *left;
		Node *right;
		Node *parent;

		Node(long long int v) : value(v), left(nullptr), right(nullptr), parent(nullptr) {}
	};

	Node *root;

	void transplant(Node *u, Node *v, long long int *comparisons, long long int *read_ptr, long long int *write_ptr) {
		
		if (u->parent == nullptr) {
			*read_ptr += 1;
			*write_ptr += 1;
			this->root = v;
		} else if (u == u->parent->left) {
			*read_ptr += 4;
			u->parent->left = v;
			*write_ptr += 1;
		} else {
			*read_ptr += 4;
			u->parent->right = v;
			*write_ptr += 1;
		}

		if (v != nullptr) {
			*write_ptr += 1;
			*read_ptr += 1;
			v->parent = u->parent;
		}
	}

	Node* search(long long int k, long long int *comparisons, long long int *read_ptr, long long int *write_ptr) {

		*read_ptr += 1;
		Node *x = this->root;

		while (x != nullptr && ++(*comparisons) && k != x->value) {

			*comparisons += 1;
			if (k < x->value) {
				*read_ptr += 1;
				x = x->left;
			} else {
				*read_ptr += 1;
				x = x->right;
			}
		}

		return x;
	}

	Node* minimum(Node *x, long long int *comparisons, long long int *read_ptr, long long int *write_ptr) {

		*read_ptr += 1;
		while (x->left != nullptr) {
			*read_ptr += 2;
			x = x->left;
		}
		return x;
	}

	std::vector<unsigned char> left_trace;
	std::vector<unsigned char> right_trace;
	
	long long int height(Node *r) {
		if (r == nullptr) {
			return -1;
		}
		long long int left_height = height(r->left);
		long long int right_height = height(r->right);
		if (left_height > right_height) {
			return 1 + left_height;
		} else {
			return 1 + right_height;
		}
	}
};

int main(int argc, char **argv) {
	long long int comparisons = 0;
	long long int read_ptr = 0;
	long long int write_ptr = 0;
	srand(time(NULL));
	BST bst;
	for (long long int i = 0; i < std::stoi(argv[1]); ++i) {
		long long int k = rand() % (2 * std::stoi(argv[1]));
		bst.insert(k, &comparisons, &read_ptr, &write_ptr);
	}
//	printf("%lld %lld %lld %lld\n", comparisons, read_ptr, write_ptr, bst.height());
	comparisons = 0;
	read_ptr = 0;
	write_ptr = 0;
	for (long long int i = 0; i < std::stoi(argv[1]); ++i) {
		long long int k = rand() % (2 * std::stoi(argv[1]));
		bst.del(k, &comparisons, &read_ptr, &write_ptr);
	}
	printf("%lld %lld %lld %lld\n", comparisons, read_ptr, write_ptr, bst.height());
}

