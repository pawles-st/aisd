#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

std::size_t comp;

struct Node {
	std::size_t key;
	std::size_t degree;
	Node *sibling;
	Node *parent;
	Node *child;

	Node() : key(0), degree(0), sibling(nullptr), parent(nullptr), child(nullptr) {}
	Node(std::size_t k) : key(k), degree(0), sibling(nullptr), parent(nullptr), child(nullptr) {}
};

class BinomialHeap {

	private:

	Node *head;
	Node *min;

	static void link(Node *y, Node *z) {
		y->parent = z;
		y->sibling = z->child;
		z->child = y;
		z->degree += 1;
	}

	static Node* merge_heads(BinomialHeap *x, BinomialHeap *y) {
		Node *merged = new Node();
		Node *curr = merged;

		Node *L = x->head;
		Node *R = y->head;
		if (L == nullptr) {
			return R;
		} else if (R == nullptr) {
			return L;
		}
		while (L != nullptr || R != nullptr) {
			if (L == nullptr) {
				curr->sibling = R;
				curr = curr->sibling;
				R = R->sibling;
			} else if (R == nullptr) {
				curr->sibling = L;
				curr = curr->sibling;
				L = L->sibling;
			} else {
				if (L->degree < R->degree) {
					curr->sibling = L;
					curr = curr->sibling;
					L = L->sibling;
				} else {
					curr->sibling = R;
					curr = curr->sibling;
					R = R->sibling;
				}
			}
		}
		return merged->sibling;
	}

	public:

	BinomialHeap() : head(nullptr), min(nullptr) {}
	BinomialHeap(Node *x) : head(x), min(x) {}

	void insert(Node *x) {
		merge(new BinomialHeap(x));
	}

	void merge(BinomialHeap *bh) {
		BinomialHeap *H = new BinomialHeap();
		H->head = merge_heads(this, bh);

		if (H->head == nullptr) {
			head = nullptr;
			min = nullptr;
			return;
		} else {
			Node *prev_x = nullptr;
			Node *x = H->head;
			Node *next_x = x->sibling;
			while (next_x != nullptr) {
				if (x->degree != next_x->degree || (next_x->sibling != nullptr && next_x->sibling->degree == x->degree)) {
					prev_x = x;
					x = next_x;
				} else if (x->key <= next_x->key) {
					comp += 1;
					x->sibling = next_x->sibling;
					link(next_x, x);
				} else {
					comp += 1;
					if (prev_x == nullptr) {
						H->head = next_x;
					} else {
						prev_x->sibling = next_x;
					}
					link(x, next_x);
					x = next_x;
				}
				next_x = x->sibling;
			}

			head = H->head;
			min = H->head;
			Node *curr = head;
			while (curr != nullptr) {
				comp += 1;
				if (curr->key < min->key) {
					min = curr;
				}
				curr = curr->sibling;
			}
		}
	}

	Node* extract_min() {
		if (min == nullptr) {
			return nullptr;
		}
		Node *min_node = min;
		Node *prev_x = nullptr;
		Node *x = head;
		while (x != min_node) {
			prev_x = x;
			x = x->sibling;
		}

		if (prev_x == nullptr) {
			head = x->sibling;
		} else {
			prev_x->sibling = x->sibling;
		}

		Node *h = nullptr;
		Node *curr = min_node->child;
		while (curr != nullptr) {
			Node *next = curr->sibling;
			curr->sibling = h;
			h = curr;
			curr = next;
		}

		BinomialHeap *H = new BinomialHeap();
		H->head = h;
		merge(H);

		return min_node;
	}
};

int main(int, char **argv) {
	srand(time(NULL));
	BinomialHeap h1;
	BinomialHeap h2;
	int n = std::stoi(argv[1]);
	std::cout << "inserting to h1:";
	for (int i = 0; i < n; ++i) {
		int k = rand() % (2 * n);
		h1.insert(new Node(k));
		std::cout << " " << k;
	}
	std::cout << "\n\ninserting to h2:";
	for (int i = 0; i < n; ++i) {
		int k = rand() % (2 * n);
		h1.insert(new Node(k));
		std::cout << " " << k;
	}
	h1.merge(&h2);
	std::cout << "\n\nextracting from merged heap:";
	Node *x;
	std::vector<int> v;
	for (int i = 0; i < 2 * n; ++i) {
		x = h1.extract_min();
		v.push_back(x->key);
		std::cout << " " << x->key;
	}
	std::cout << "\n\n";
	assert(std::is_sorted(std::begin(v), std::end(v)));
	if (h1.extract_min() == nullptr) {
		std::cout << "heap is empty\n";
	}
//	std::cout << comp << "\n";
}
