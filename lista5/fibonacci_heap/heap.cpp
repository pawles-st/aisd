#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

std::size_t comp = 0;

struct Node {
	std::size_t key;
	std::size_t degree;
	Node *right;
	Node *left;
	Node *parent;
	Node *child;
	bool marked;

	Node() : key(0), degree(0), right(nullptr), left(nullptr), parent(nullptr), child(nullptr), marked(false) {}
	Node(std::size_t k) : key(k), degree(0), right(nullptr), left(nullptr), parent(nullptr), child(nullptr), marked(false) {}
};

class FibonacciHeap {

	private:

	Node *min;
	std::size_t no_nodes;

	public:

	FibonacciHeap() : min(nullptr), no_nodes(0) {}
	FibonacciHeap(Node *n) : min(n), no_nodes(1) {
		n->right = n;
		n->left = n;
		n->parent = nullptr;
		n->child = nullptr;
	}

	void insert(Node *n) {
		merge(new FibonacciHeap(n));
	}

	void merge(FibonacciHeap *fh) {
		no_nodes += fh->no_nodes;
		if (fh->min == nullptr) {
			return;
		} else if (min == nullptr) {
			min = fh->min;
			return;
		} else {
			Node *first1 = min;
			Node *last1 = min->right;
			Node *first2 = fh->min;
			Node *last2 = fh->min->right;
			first1->right = last2;
			last1->left = first2;
			first2->right = last1;
			last2->left = first1;
			comp += 1;
			if (fh->min->key < min->key) {
				min = fh->min;
			}
		}
	}

	Node* extract_min() {
		if (min == nullptr) {
			return nullptr;
		}
		no_nodes -= 1;
		Node *min_node = min;

		if (min_node->left == min_node) {
			min = nullptr;
		} else {
			Node *prev = min_node->right;
			Node *next = min_node->left;
			prev->left = next;
			next->right = prev;
			min = next;
		}

		if (min_node->child != nullptr) {
			Node *first_child = min_node->child;
			Node *curr_child = first_child;

			do {
				curr_child->parent = nullptr;
				curr_child = curr_child->left;
			} while (curr_child != first_child);

			if (min == nullptr) {
				min = first_child;
			} else {
				Node *first1 = min;
				Node *last1 = min->right;
				Node *first2 = first_child;
				Node *last2 = first_child->right;
				first1->right = last2;
				last1->left = first2;
				first2->right = last1;
				last2->left = first1;
			}
		}

		if (min != nullptr) {
			std::size_t max_other_size = 5 * (static_cast<std::size_t>(std::log2(no_nodes + 1)) + 1);
			Node *other[max_other_size + 1];
			for (std::size_t i = 0; i <= max_other_size; ++i) {
				other[i] = nullptr;
			}
			std::size_t max_degree = 0;
			Node *curr = min;
			do {
				Node *next = curr->left;
				std::size_t other_degree = curr->degree;
				Node *P = curr;
				while (other[other_degree] != nullptr) {
					Node *Q = other[other_degree];
					other[other_degree] = nullptr;

					comp += 1;
					if (P->key > Q->key) {
						Node *temp = P;
						P = Q;
						Q = temp;
					}

					Q->parent = P;
					if (P->child == nullptr) {
						P->child = Q;
						Q->right = Q;
						Q->left = Q;
					} else {
						Node *last = P->child->right;
						last->left = Q;
						Q->right = last;
						P->child->right = Q;
						Q->left = P->child;
					}

					other_degree += 1;
					P->degree = other_degree;
				}

				other[other_degree] = P;
				if (other_degree > max_degree) {
					max_degree = other_degree;
				}
				curr = next;
			} while (curr != min);

			Node *previous = other[max_degree];
			min = previous;
			for (std::size_t i = 0; i <= max_degree; ++i) {
				if (other[i] != nullptr) {
					previous->left = other[i];
					other[i]->right = previous;

					comp += 1;
					if (other[i]->key < min->key) {
						min = other[i];
					}
					previous = other[i];
				}
			}
		}

		return min_node;
	}
};

int main(int, char **argv) {
	srand(time(NULL));
	FibonacciHeap h1;
	FibonacciHeap h2;
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
