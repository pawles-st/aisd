#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
using Matrix = std::vector<std::vector<T>>;

std::pair<Matrix<std::size_t>, Matrix<char>> lcs_length(const std::string& p, const std::string& q) {
	std::size_t comp = 0;
	const std::string x = " " + p;
	const std::string y = " " + q;
	const std::size_t m = p.size();
	const std::size_t n = q.size();
	Matrix<char> b(m + 1, std::vector<char>(n + 1, ' '));
	Matrix<std::size_t> c(m + 1, std::vector<std::size_t>(n + 1, 0));
	for (std::size_t i = 1; i <= m; ++i) {
		for (std::size_t j = 1; j <= n; ++j) {
			if (x[i] == y[j]) {
				comp += 1;
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 'q';
			} else if (c[i - 1][j] >= c[i][j - 1]) {
				comp += 2;
				c[i][j] = c[i - 1][j];
				b[i][j] = '^';
			} else {
				comp += 2;
				c[i][j] = c[i][j - 1];
				b[i][j] = '<';
			}
		}
	}
//	std::cout << comp << "\n";
	return std::pair<Matrix<std::size_t>, Matrix<char>>(c, b);
}

void print_lcs(const Matrix<char>& b, const std::string& x, std::size_t i, std::size_t j) {
	if (i == 0 || j == 0) {
		return;
	} else if (b[i][j] == 'q') {
		print_lcs(b, x, i - 1, j - 1);
		std::cout << x[i - 1];
	} else if (b[i][j] == '^') {
		print_lcs(b, x, i - 1, j);
	} else {
		print_lcs(b, x, i, j - 1);
	}
}

int main(int, char **argv) {
	{
		std::string x = "abcdbacadbacadbacdabcadababac";
		std::string y = "dbcadbdcacbdacbaccadbadcadabd";
		std::cout << "first string: " << x << "\n";
		std::cout << "second string: " << y << "\n\n";
		std::size_t m = x.size();
		std::size_t n = y.size();
		std::pair<Matrix<std::size_t>, Matrix<char>> lcs = lcs_length(x, y);
		std::cout << "length of lcs: " << lcs.first[m][n] << "\n";
		std::cout << "longest common substring: ";
		print_lcs(lcs.second, x, m, n);
		std::cout << "\n-----\n";
	}
	{
		std::string x = "ACCGGTCGAGTGCGCGGAAGCCGGCCAA";
		std::string y = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
		std::cout << "first string: " << x << "\n";
		std::cout << "second string: " << y << "\n\n";
		std::size_t m = x.size();
		std::size_t n = y.size();
		std::pair<Matrix<std::size_t>, Matrix<char>> lcs = lcs_length(x, y);
		std::cout << "length of lcs: " << lcs.first[m][n] << "\n";
		std::cout << "longest common substring: ";
		print_lcs(lcs.second, x, m, n);
		std::cout << "\n-----\n";
	}
	{
		std::string x = "ABCBDAB";
		std::string y = "BDCABA";
		std::cout << "first string: " << x << "\n";
		std::cout << "second string: " << y << "\n\n";
		std::size_t m = x.size();
		std::size_t n = y.size();
		std::pair<Matrix<std::size_t>, Matrix<char>> lcs = lcs_length(x, y);
		std::cout << "length of lcs: " << lcs.first[m][n] << "\n";
		std::cout << "longest common substring: ";
		print_lcs(lcs.second, x, m, n);
		std::cout << "\n";
	}
	/*
	srand(time(NULL));
	std::size_t k = std::stoi(argv[1]);
	std::string x = "";
	std::string y = "";
	for (std::size_t i = 0; i < k; ++i) {
		x += static_cast<char>(65 + rand() % 26);
		y += static_cast<char>(65 + rand() % 26);
	}
//	std::cout << "first string: " << x << "\n";
//	std::cout << "second string: " << y << "\n\n";
	std::size_t m = x.size();
	std::size_t n = y.size();
	std::pair<Matrix<std::size_t>, Matrix<char>> lcs = lcs_length(x, y);
	*/
//	std::cout << "length of lcs: " << lcs.first[m][n] << "\n";
//	std::cout << "longest common substring: ";
//	print_lcs(lcs.second, x, m, n);
//	std::cout << "\n";
	/*
	std::cout << "\n\nMatrix of subproblems:\n\n";
	for (std::size_t i = 0; i <= m; ++i) {
		for (std::size_t j = 0; j <= n; ++j) {
			std::cout << lcs.second[i][j];
		}
		std::cout << "\n";
	}
	*/
}
