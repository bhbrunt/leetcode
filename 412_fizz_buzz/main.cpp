#include <vector>
#include <string>
#include <iostream>
#include <chrono>

class Solution {
	public:
		std::vector<std::string> fizzBuzz(int n) {
			std::vector<string> output;

			for (int i=1; i<=n; i++) {
				std::string val;
				if (i % 15 == 0) {
					val = "FizzBuzz";
				} else if (i % 3 == 0) {
					val = "Fizz";
				} else if (i % 5 == 0) {
					val = "Buzz";
				} else {
					val = std::to_string(i);
				}
				output.push_back(val);
			}

			return output;
		}
};

int main() {
	const int test_case = 15;

	Solution solution;
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::string> output = solution.fizzBuzz(test_case);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Output = ";
	for (const std::string& val : output) {
		std::cout << val << ", ";
	}
	std::cout << std::endl;
	std::cout << "Duration: " << duration.count() << " ms" << std::endl;

	return 0;
}
