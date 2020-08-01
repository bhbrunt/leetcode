#include <iostream>
#include <string>
#include <stack>
#include <chrono>
#include <cassert>

class Solution {
	public:
		bool isValid(std::string s) {
			std::stack<char> char_stack;
			for (char& c : s) {
				if (char_stack.empty()) {
					char_stack.push(c);
				} else if (isOpeningBracket(c)) {
					char_stack.push(c);
				} else if (isMatchingClose(char_stack.top(), c)) {
					char_stack.pop();
				} else {
					// A closing bracket that doesn't match last opening bracket.
					return false;
				}
			}
			return char_stack.empty();
		}
	private:
		bool isOpeningBracket(char c) {
			return (c == '(' || c == '{' || c == '[' );
		}
		bool isMatchingClose(char open, char c) {
			switch (open) {
				case '(': return (c == ')');
				case '{': return (c == '}');
				case '[': return (c == ']');
			}
			return false;
		}
};

int main() {
	const std::string test_case = "([)]";

	Solution solution;
	auto start = std::chrono::high_resolution_clock::now();
	int output = solution.isValid(test_case);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Output = " << output << std::endl;
	std::cout << "Duration: " << duration.count() << " ms" << std::endl;
	assert(output == false);

	return 0;
}
