#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

class Splay {
	public:
	
	Splay() : root(nullptr) {}

	void insert(int k) {
		Node *y = nullptr;
		Node *x = this->root;

		while (x != nullptr) {
			y = x;
			if (k < x->value) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		Node *new_node = new Node(k);
		new_node->parent = y;

		if (y == nullptr) {
			this->root = new_node;
		} else if (k < y->value) {
			y->left = new_node;
		} else {
			y->right = new_node;
		}

		splay(new_node);
	}

	bool del(int k) {
		Node *z = search(k);
		if (z == nullptr) {
			return false;
		} else {
			splay(z);
			if (z->left == nullptr) {
				transplant(z, z->right);
			} else if (z->right == nullptr) {
				transplant(z, z->left);
			} else {
				Node *y = minimum(z->right);
				if (y->parent != z) {
					transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
			}
			delete z;
			return true;
		}
	}

	int height() {
		if (this->root == nullptr) {
			return -1;
		} else {
			return height(this->root);
		}
	}

	void print() {
		print(this->root, 0, '-');
	}

	private:

	struct Node {
		int value;
		Node *left;
		Node *right;
		Node *parent;

		Node(int v) : value(v), left(nullptr), right(nullptr), parent(nullptr) {}
	};

	Node *root;

	void transplant(Node *u, Node *v) {
		if (u->parent == nullptr) {
			this->root = v;
		} else if (u == u->parent->left) {
			u->parent->left = v;
		} else {
			u->parent->right = v;
		}
		if (v != nullptr) {
			v->parent = u->parent;
		}
	}

	Node* search(int k) {
		Node *x = this->root;
		while (x != nullptr && k != x->value) {
			if (k < x->value) {
				x = x->left;
			} else {
				x = x->right;
			}
		}
		return x;
	}

	Node* minimum(Node *x) {
		while (x->left != nullptr) {
			x = x->left;
		}
		return x;
	}
	
	void left_rotate(Node *x) {
		Node *y = x->right;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void right_rotate(Node *x) {
		Node *y = x->left;
		x->left = y->right;
		if (y->right != nullptr) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->right = x;
		x->parent = y;
	}

	void splay(Node *x) {
		while (x->parent != nullptr) {
			if (x->parent->parent == nullptr) {
				if (x == x->parent->left) {
					right_rotate(x->parent);
				} else {
					left_rotate(x->parent);
				}
			} else {
				if (x == x->parent->left && x->parent == x->parent->parent->left) {
					right_rotate(x->parent->parent);
					right_rotate(x->parent);
				} else if (x == x->parent->right && x->parent == x->parent->parent->right) {
					left_rotate(x->parent->parent);
					left_rotate(x->parent);
				} else if (x == x->parent->right && x->parent == x->parent->parent->left) {
					left_rotate(x->parent);
					right_rotate(x->parent);
				} else {
					right_rotate(x->parent);
					left_rotate(x->parent);
				}
			}
		}
	}

	std::vector<unsigned char> left_trace;
	std::vector<unsigned char> right_trace;

	void print(Node *r, size_t depth, char prefix) {
		if (left_trace.size() <= depth || right_trace.size() <= depth) {
			left_trace.resize(1 + left_trace.size() * 10, 0);
			right_trace.resize(1 + right_trace.size() * 10, 0);
		}
		if (r == nullptr) { return; }
		if (r->left != nullptr) {
			print(r->left, depth + 1, '/');
		}
		if (prefix == '/') { left_trace[depth - 1] = '|'; }
		if (prefix == '\\') { right_trace[depth - 1] = ' '; }
		if (depth == 0) { printf("-"); }
		if (depth > 0) { printf(" "); }
		for (size_t i = 1; i < depth; ++i) {
			if (left_trace[i - 1] == '|' || right_trace[i - 1] == '|') {
				printf("| ");
			} else {
				printf("  ");
			}
		}
		if (depth > 0) { printf("%c-", prefix); }
		printf("[%d]\n", r->value);
		left_trace[depth] = ' ';
		if (r->right != nullptr) {
			right_trace[depth] = '|';
			print(r->right, depth + 1, '\\');
		}
	}

	int height(Node *r) {
		if (r == nullptr) {
			return -1;
		}
		int left_height = height(r->left);
		int right_height = height(r->right);
		if (left_height > right_height) {
			return 1 + left_height;
		} else {
			return 1 + right_height;
		}
	}
};

int main() {
	srand(time(NULL));
	Splay splay;
	for (int i = 0; i < 50; ++i) {
		int k = rand() % 100;
		printf("insert %d\n", i);
		splay.insert(i);
		splay.print();
	}
	printf("height %d\n", splay.height());
	usleep(2000000);
	for (int i = 0; i < 50; ++i) {
		int k = rand() % 100;
		printf("delete %d\n", k);
		splay.del(k);
		splay.print();
	}
	printf("height %d\n", splay.height());
}
