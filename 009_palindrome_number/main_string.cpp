#include <iostream>
#include <chrono>
#include <cassert>

class Solution {
public:
    bool isPalindrome(int x) {
      if (x<0) return false;
      if (x==0) return true;

			std::string x_str = std::to_string(x);

			auto it  = x_str.begin();
			auto rit = x_str.rbegin();
			while (it < x_str.end()) {
				if (*it != *rit) return false;
				++it; ++rit;
			}

      return true;
    }
};

int main() {
	const int test_case = 1234554321;

	Solution solution;
	auto start = std::chrono::high_resolution_clock::now();
	int output = solution.isPalindrome(test_case);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Output = " << output << std::endl;
	std::cout << "Duration: " << duration.count() << " ms" << std::endl;
	assert(output == true);

	return 0;
}
