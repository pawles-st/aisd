#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

class RBBST {
	public:
	
	RBBST() : root(nil) {}
	~RBBST() {
		delete nil;
	}

	void insert(int k) {
		Node *y = nil;
		Node *x = this->root;

		while (x != nil) {
			y = x;
			if (k < x->value) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		Node *new_node = new Node(k, nil);
		new_node->parent = y;

		if (y == nil) {
			this->root = new_node;
		} else if (k < y->value) {
			y->left = new_node;
		} else {
			y->right = new_node;
		}

		insert_fixup(new_node);
	}

	bool del(int k) {
		Node *z = search(k);
		Node *y = z;
		Node *x;
		Colour y_original_colour = y->colour;
		if (z == nil) {
			return false;
		} else {
			if (z->left == nil) {
				x = z->right;
				transplant(z, z->right);
			} else if (z-> right == nil) {
				x = z->left;
				transplant(z, z->left);
			} else {
				Node *y = minimum(z->right);
				y_original_colour = y->colour;
				x = y->right;
				if (y->parent == z) {
					x->parent = y;
				} else {
					transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->colour = z->colour;
			}
			delete z;
			if (y_original_colour == black) {
				delete_fixup(x);
			}
			return true;
		}
	}

	int height() {
		if (this->root == nil) {
			return -1;
		} else {
			return height(this->root);
		}
	}

	void print() {
		print(this->root, 0, '-');
	}

	private:

	enum Colour {
		red, black
	};

	struct Node {
		int value;
		Node *left;
		Node *right;
		Node *parent;
		Colour colour;

		Node(int v, Node *nil) : value(v), left(nil), right(nil), parent(nil), colour(red) {}
		Node() : left(nullptr), right(nullptr), parent(nullptr), colour(black) {}
	};

	Node *nil = new Node();
	Node *root;

	void transplant(Node *u, Node *v) {
		if (u->parent == nil) {
			this->root = v;
		} else if (u == u->parent->left) {
			u->parent->left = v;
		} else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	Node* search(int k) {
		Node *x = this->root;
		while (x != nil && k != x->value) {
			if (k < x->value) {
				x = x->left;
			} else {
				x = x->right;
			}
		}
		return x;
	}

	Node* minimum(Node *x) {
		while (x->left != nil) {
			x = x->left;
		}
		return x;
	}

	void left_rotate(Node *x) {
		Node *y = x->right;
		x->right = y->left;
		if (y->left != nil) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nil) {
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
		if (y->right != nil) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nil) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->right = x;
		x->parent = y;
	}

	void insert_fixup(Node *z) {
		while (z->parent->colour == red) {
			if (z->parent == z->parent->parent->left) {
				Node *y = z->parent->parent->right;
				if (y->colour == red) {
					z->parent->colour = black;
					y->colour = black;
					z->parent->parent->colour = red;
					z = z->parent->parent;
				} else {
					if (z == z->parent->right) {
						z = z->parent;
						left_rotate(z);
					}
					z->parent->colour = black;
					z->parent->parent->colour = red;
					right_rotate(z->parent->parent);
				}
			}
			else {
				Node *y = z->parent->parent->left;
				if (y->colour == red) {
					z->parent->colour = black;
					y->colour = black;
					z->parent->parent->colour = red;
					z = z->parent->parent;
				} else if (z == z->parent->left) {
					z = z->parent;
					right_rotate(z);
				} else {
					z->parent->colour = black;
					z->parent->parent->colour = red;
					left_rotate(z->parent->parent);
				}
			}
		}
		this->root->colour = black;
	}

	void delete_fixup(Node *x) {
		while (x != this->root && x->colour == black) {
			if (x == x->parent->left) {
				Node *w = x->parent->right;
				if (w->colour == red) {
					w->colour = black;
					x->parent->colour = red;
					left_rotate(x->parent);
					w = x->parent->right;
				}
				if (w->left->colour == black && w->right->colour == black) {
					w->colour = red;
					x = x->parent;
				} else {
					if (w->right->colour == black) {
						w->left->colour = black;
						w->colour = red;
						right_rotate(w);
						w = x->parent->right;
					}
					w->colour = x->parent->colour;
					x->parent->colour = black;
					w->right->colour = black;
					left_rotate(x->parent);
					x = this->root;
				}
			} else {
				Node *w = x->parent->left;
				if (w->colour == red) {
					w->colour = black;
					x->parent->colour = red;
					right_rotate(x->parent);
					w = x->parent->left;
				}
				if (w->right->colour == black && w->left->colour == black) {
					w->colour = red;
					x = x->parent;
				} else {
					if (w->left->colour == black) {
						w->right->colour = black;
						w->colour = red;
						left_rotate(w);
						w = x->parent->left;
					}
					w->colour = x->parent->colour;
					x->parent->colour = black;
					w->left->colour = black;
					right_rotate(x->parent);
					x = this->root;
				}
			}
		}
		x->colour = black;
	}

	std::vector<unsigned char> left_trace;
	std::vector<unsigned char> right_trace;

	void print(Node *r, size_t depth, char prefix) {
		if (left_trace.size() <= depth || right_trace.size() <= depth) {
			left_trace.resize(1 + left_trace.size() * 10, 0);
			right_trace.resize(1 + right_trace.size() * 10, 0);
		}
		if (r == nil) { return; }
		if (r->left != nil) {
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
		printf("[%d ", r->value);
		if (r->colour == red) {
			printf("R]\n");
		} else {
			printf("B]\n");
		}
		left_trace[depth] = ' ';
		if (r->right != nil) {
			right_trace[depth] = '|';
			print(r->right, depth + 1, '\\');
		}
	}

	int height(Node *r) {
		if (r == nil) {
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
	RBBST rb;
	for (int i = 0; i < 50; ++i) {
		int k = rand() % 100;
		printf("insert %d\n", i);
		rb.insert(i);
		rb.print();
	}
	printf("height %d\n", rb.height());
	usleep(2000000);
	for (int i = 0; i < 50; ++i) {
		int k = rand() % 100;
		printf("delete %d\n", k);
		rb.del(k);
		rb.print();
	}
	printf("height %d\n", rb.height());
}
