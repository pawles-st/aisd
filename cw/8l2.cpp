#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int prepare(std::vector<int>::const_iterator A_begin, std::vector<int>::const_iterator A_end, std::vector<int>& B) {
	if (A_begin == A_end) { 
		B.push_back(*A_begin);
		return *A_begin;
	}
	int l = prepare(A_begin, A_begin + std::distance(A_begin, A_end) / 2, B);
	int r = prepare(A_begin + std::distance(A_begin, A_end) / 2, A_end, B);
	B.push_back(l + r);
	return l + r;
}

int main() {
	const std::vector<int> A = {1, 7, 8, 9, 5, 1, 4};
	std::vector<int> B;
	prepare(std::begin(A), std::end(A), B);
}
