#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class RBBST {
	public:
	
	RBBST() : root(nil) {}
	~RBBST() {
		delete nil;
	}

	void insert(long long int k, long long int *comparisons, long long int *read_ptr, long long int *write_ptr) {
		Node *y = nil;
		*read_ptr += 1;
		Node *x = this->root;

		while (x != nil) {
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

		Node *new_node = new Node(k, nil);
		*write_ptr += 1;
		new_node->parent = y;

		if (y == nil) {
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

		insert_fixup(new_node, comparisons, read_ptr, write_ptr);
	}

	bool del(long long int k, long long int *comparisons, long long int *read_ptr, long long int *write_ptr) {

		Node *z = search(k, comparisons, read_ptr, write_ptr);
		Node *y = z;
		Node *x;
		Colour y_original_colour = y->colour;

		if (z == nil) {

			return false;

		} else {

			if (z->left == nil) {

				*read_ptr += 2;
				x = z->right;
				transplant(z, z->right, comparisons, read_ptr, write_ptr);

			} else if (z-> right == nil) {

				*read_ptr += 3;
				x = z->left;
				transplant(z, z->left, comparisons, read_ptr, write_ptr);

			} else {

				*read_ptr += 3;
				Node *y = minimum(z->right, comparisons, read_ptr, write_ptr);
				y_original_colour = y->colour;

				*read_ptr += 1;
				x = y->right;

				*read_ptr += 1;
				if (y->parent == z) {
					
					*write_ptr += 1;
					x->parent = y;

				} else {

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
				y->colour = z->colour;
			}

			delete z;

			if (y_original_colour == black) {
				delete_fixup(x, comparisons, read_ptr, write_ptr);
			}

			return true;
		}
	}

	long long int height() {
		if (this->root == nil) {
			return -1;
		} else {
			return height(this->root);
		}
	}

	private:

	enum Colour {
		red, black
	};

	struct Node {
		long long int value;
		Node *left;
		Node *right;
		Node *parent;
		Colour colour;

		Node(long long int v, Node *nil) : value(v), left(nil), right(nil), parent(nil), colour(red) {}
		Node() : left(nullptr), right(nullptr), parent(nullptr), colour(black) {}
	};

	Node *nil = new Node();
	Node *root;

	void transplant(Node *u, Node *v, long long int *comparisons, long long int *read_ptr, long long int *write_ptr) {

		if (u->parent == nil) {
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

		*read_ptr += 1;
		*write_ptr += 1;
		v->parent = u->parent;
	}

	Node* search(long long int k, long long int *comparisons, long long int *read_ptr, long long int *write_ptr) {

		*read_ptr += 1;
		Node *x = this->root;

		while (x != nil && ++(*comparisons) && k != x->value) {

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
		while (x->left != nil) {
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
		if (y->left != nil) {

			*read_ptr += 1;
			*write_ptr += 1;
			y->left->parent = x;

		}

		*read_ptr += 1;
		*write_ptr += 1;
		y->parent = x->parent;

		if (x->parent == nil) {

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
		if (y->right != nil) {

			*read_ptr += 1;
			*write_ptr += 1;
			y->right->parent = x;

		}

		*read_ptr += 1;
		*write_ptr += 1;
		y->parent = x->parent;

		if (x->parent == nil) {

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

	void insert_fixup(Node *z, long long int *comparisons, long long int *read_ptr, long long int *write_ptr) {

		while (++(*read_ptr) && z->parent->colour == red) {

			*read_ptr += 4;
			if (z->parent == z->parent->parent->left) {

				*read_ptr += 3;
				Node *y = z->parent->parent->right;

				if (y->colour == red) {

					*read_ptr += 5;
					z->parent->colour = black;
					y->colour = black;
					z->parent->parent->colour = red;
					z = z->parent->parent;

				} else {

					*read_ptr += 7;
					if (z == z->parent->right) {

						*read_ptr += 1;
						z = z->parent;
						left_rotate(z, comparisons, read_ptr, write_ptr);

					}

					z->parent->colour = black;
					z->parent->parent->colour = red;
					right_rotate(z->parent->parent, comparisons, read_ptr, write_ptr);

				}
			}
			else {

				*read_ptr += 3;
				Node *y = z->parent->parent->left;

				if (y->colour == red) {

					*read_ptr += 5;
					z->parent->colour = black;
					y->colour = black;
					z->parent->parent->colour = red;
					z = z->parent->parent;

				} else if (z == z->parent->left) {

					*read_ptr += 1;
					z = z->parent;
					right_rotate(z, comparisons, read_ptr, write_ptr);

				} else {

					*read_ptr += 5;
					z->parent->colour = black;
					z->parent->parent->colour = red;
					left_rotate(z->parent->parent, comparisons, read_ptr, write_ptr);

				}
			}
		}

		*read_ptr += 1;
		this->root->colour = black;
	}

	void delete_fixup(Node *x, long long int *comparisons, long long int *read_ptr, long long int *write_ptr) {
		while (++(*read_ptr) && x != this->root && x->colour == black) {

			*read_ptr += 2;
			if (x == x->parent->left) {

				*read_ptr += 2;
				Node *w = x->parent->right;

				if (w->colour == red) {

					*read_ptr += 4;
					w->colour = black;
					x->parent->colour = red;
					left_rotate(x->parent, comparisons, read_ptr, write_ptr);
					w = x->parent->right;

				}

				*read_ptr += 2;
				if (w->left->colour == black && w->right->colour == black) {

					*read_ptr += 1;
					w->colour = red;
					x = x->parent;

				} else {

					*read_ptr += 1;
					if (w->right->colour == black) {

						*read_ptr += 2;
						w->left->colour = black;
						w->colour = red;
						right_rotate(w, comparisons, read_ptr, write_ptr);
						w = x->parent->right;

					}

					*read_ptr += 5;
					w->colour = x->parent->colour;
					x->parent->colour = black;
					w->right->colour = black;
					left_rotate(x->parent, comparisons, read_ptr, write_ptr);
					x = this->root;

				}
			} else {

				*read_ptr += 2;
				Node *w = x->parent->left;

				if (w->colour == red) {

					*read_ptr += 4;
					w->colour = black;
					x->parent->colour = red;
					right_rotate(x->parent, comparisons, read_ptr, write_ptr);
					w = x->parent->left;

				}

				*read_ptr += 2;
				if (w->right->colour == black && w->left->colour == black) {

					*read_ptr += 1;
					w->colour = red;
					x = x->parent;

				} else {

					*read_ptr += 1;
					if (w->left->colour == black) {

						*read_ptr += 2;
						w->right->colour = black;
						w->colour = red;
						left_rotate(w, comparisons, read_ptr, write_ptr);
						w = x->parent->left;

					}

					*read_ptr += 5;
					w->colour = x->parent->colour;
					x->parent->colour = black;
					w->left->colour = black;
					right_rotate(x->parent, comparisons, read_ptr, write_ptr);
					x = this->root;

				}
			}
		}
		x->colour = black;
	}

	std::vector<unsigned char> left_trace;
	std::vector<unsigned char> right_trace;

	long long int height(Node *r) {
		if (r == nil) {
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
	RBBST rb;
	for (long long int i = 0; i < std::stoi(argv[1]); ++i) {
		long long int k = rand() % (2 * std::stoi(argv[1]));
		rb.insert(k, &comparisons, &read_ptr, &write_ptr);
	}
//	printf("%lld %lld %lld %lld\n", comparisons, read_ptr, write_ptr, rb.height());
	comparisons = 0;
	read_ptr = 0;
	write_ptr = 0;
	for (long long int i = 0; i < std::stoi(argv[1]); ++i) {
		long long int k = rand() % (2 * std::stoi(argv[1]));
		rb.del(k, &comparisons, &read_ptr, &write_ptr);
	}
	printf("%lld %lld %lld %lld\n", comparisons, read_ptr, write_ptr, rb.height());
}
