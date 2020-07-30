#include <math.h>
#include <vector>
#include <iostream>
#include <chrono>
#include <cassert>

class Solution {
public:
    bool isPalindrome(int x) {
      if (x<0) return false;
      if (x==0) return true;

      std::vector<int> digits;
      const int smaller_power_of_ten = std::floor(std::log10(x));
      for (int i=smaller_power_of_ten; i>=0; i--) {
        const int this_power = pow(10,i);
        const int digit = x / this_power;
        x -= digit*this_power;
        digits.push_back(digit);
      }

      const size_t len_digits(digits.size());
      const size_t limit = (len_digits % 2 == 0 ? len_digits/2 : len_digits/2+1);
      for (size_t i=0; i<limit; i++) {
        if (digits[i] != digits[len_digits-1-i]) {
          return false;
        }
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
