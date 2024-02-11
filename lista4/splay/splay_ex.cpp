#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Splay {
	public:
	
	Splay() : root(nullptr) {}

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

		splay(new_node, comparisons, read_ptr, write_ptr);
	}

	bool del(long long int k, long long int *comparisons, long long int *read_ptr, long long int *write_ptr) {

		Node *z = search(k, comparisons, read_ptr, write_ptr);
		
		if (z == nullptr) {

			return false;

		} else {

			splay(z, comparisons, read_ptr, write_ptr);

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
	
	void left_rotate(Node *x, long long int *comparisons, long long int *read_ptr, long long int *write_ptr) {

		*read_ptr += 1;
		Node *y = x->right;

		*read_ptr += 1;
		*write_ptr += 1;
		x->right = y->left;

		*read_ptr += 1;
		if (y->left != nullptr) {

			*read_ptr += 1;
			*write_ptr += 1;
			y->left->parent = x;

		}

		*read_ptr += 1;
		*write_ptr += 1;
		y->parent = x->parent;

		if (x->parent == nullptr) {

			*read_ptr += 1;
			*write_ptr += 1;
			this->root = y;

		} else if (x == x->parent->left) {

			*read_ptr += 4;
			*write_ptr += 1;
			x->parent->left = y;

		} else {

			*read_ptr += 4;
			*write_ptr += 1;
			x->parent->right = y;

		}

		*write_ptr += 2;
		y->left = x;
		x->parent = y;

	}

	void right_rotate(Node *x, long long int *comparisons, long long int *read_ptr, long long int *write_ptr) {

		*read_ptr += 1;
		Node *y = x->left;

		*read_ptr += 1;
		*write_ptr += 1;
		x->left = y->right;

		*read_ptr += 1;
		if (y->right != nullptr) {

			*read_ptr += 1;
			*write_ptr += 1;
			y->right->parent = x;

		}

		*read_ptr += 1;
		*write_ptr += 1;
		y->parent = x->parent;

		if (x->parent == nullptr) {

			*read_ptr += 1;
			*write_ptr += 1;
			this->root = y;

		} else if (x == x->parent->left) {

			*read_ptr += 4;
			*write_ptr += 1;
			x->parent->left = y;

		} else {
			
			*read_ptr += 4;
			*write_ptr += 1;
			x->parent->right = y;

		}

		*write_ptr += 2;
		y->right = x;
		x->parent = y;
	}

	void splay(Node *x, long long int *comparisons, long long int *read_ptr, long long int *write_ptr) {

		*read_ptr += 1;
		while (x->parent != nullptr) {

			*read_ptr += 2;
			if (x->parent->parent == nullptr) {

				*read_ptr += 3;
				if (x == x->parent->left) {
					right_rotate(x->parent, comparisons, read_ptr, write_ptr);
				} else {
					left_rotate(x->parent, comparisons, read_ptr, write_ptr);
				}
			} else {

				if (x == x->parent->left && x->parent == x->parent->parent->left) {
//					*read_ptr += 9;
//					*read_ptr += 4;
					right_rotate(x->parent->parent, comparisons, read_ptr, write_ptr);
					right_rotate(x->parent, comparisons, read_ptr, write_ptr);
				} else if (x == x->parent->right && x->parent == x->parent->parent->right) {
//					*read_ptr += 18;
//					*read_ptr += 6;
					left_rotate(x->parent->parent, comparisons, read_ptr, write_ptr);
					left_rotate(x->parent, comparisons, read_ptr, write_ptr);
				} else if (x == x->parent->right && x->parent == x->parent->parent->left) {
//					*read_ptr += 26;
//					*read_ptr += 6;
					left_rotate(x->parent, comparisons, read_ptr, write_ptr);
					right_rotate(x->parent, comparisons, read_ptr, write_ptr);
				} else {
//					*read_ptr += 28;
//					*read_ptr += 6;
					right_rotate(x->parent, comparisons, read_ptr, write_ptr);
					left_rotate(x->parent, comparisons, read_ptr, write_ptr);
				}
			}
		}
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
	Splay splay;
	for (long long int i = 0; i < std::stoi(argv[1]); ++i) {
		long long int k = rand() % (2 * std::stoi(argv[1]));
		splay.insert(k, &comparisons, &read_ptr, &write_ptr);
	}
//	printf("%lld %lld %lld %lld\n", comparisons, read_ptr, write_ptr, splay.height());
	comparisons = 0;
	read_ptr = 0;
	write_ptr = 0;
	for (long long int i = 0; i < std::stoi(argv[1]); ++i) {
		long long int k = rand() % (2 * std::stoi(argv[1]));
		splay.del(k, &comparisons, &read_ptr, &write_ptr);
	}
	printf("%lld %lld %lld %lld\n", comparisons, read_ptr, write_ptr, splay.height());
}
