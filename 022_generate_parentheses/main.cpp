#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <string>
#include <chrono>
#include <cassert>

class Solution {
	public:
    Solution() {
      memo.insert(std::make_pair(1, std::set<std::string>({"()"})));
    };
		std::vector<std::string> generateParenthesis(int n) {
      std::set<std::string> combinations;
      if (memo.find(n) != memo.end()) {
        return std::vector<std::string>(memo.at(n).begin(), memo.at(n).end());
      }

      for (int i=1; i<n; i++) {
        std::set<std::string> appended = append(generateParenthesis(i), generateParenthesis(n-i));
        combinations.insert(appended.begin(), appended.end());
      }
      std::set<std::string> enclosed = enclose(generateParenthesis(n-1));
      combinations.insert(enclosed.begin(), enclosed.end());
      memo.insert(std::make_pair(n, combinations));
      return std::vector<std::string>(combinations.begin(), combinations.end());
    }
private:
    std::unordered_map<int, std::set<std::string>> memo;
    std::set<std::string> append(std::vector<std::string> input1, std::vector<std::string> input2) {
      std::set<std::string> output;
      for (const std::string& s1 : input1) {
        for (const std::string& s2 : input2) {
          output.insert(s1+s2);
        }
      }

      return output;
    }
    std::set<std::string> enclose(std::vector<std::string> input) {
      std::set<std::string> output;
      for (const std::string& s : input) {
        output.insert('('+s+')');
      }
      return output;
    }
};

int main() {
	const int test_case = 3;

	Solution solution;
	auto start = std::chrono::high_resolution_clock::now();
	auto output = solution.generateParenthesis(test_case);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Output = ";
	for (const auto& i : output) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	std::cout << "Duration: " << duration.count() << " ms" << std::endl;
	assert(output.size() == 5);

	return 0;
}
