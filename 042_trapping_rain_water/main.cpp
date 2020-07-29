#include <vector>
#include <iostream>
#include <chrono>

class Solution {
	public:
		int trap(std::vector<int>& height) {
			if (height.size() == 0) return 0;

			int bounding_height(0), water_trapped(0);

			size_t i(0), j(height.size()-1);
			while (j>i) {
				bounding_height = std::max(bounding_height, std::min(height[i], height[j]));
				if (height[i] < height[j]) {
					water_trapped += std::max(0, bounding_height - height[++i]);
				} else {
					water_trapped += std::max(0, bounding_height - height[--j]);
				}
			}

			return water_trapped;
		}
};

int main() {
	std::vector<int> test_case = {0,1,0,2,1,0,1,3,2,1,2,1};

	Solution solution;
	auto start = std::chrono::high_resolution_clock::now();
	int output = solution.trap(test_case);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Output = " << output << std::endl;
	std::cout << "Duration: " << duration.count() << " ms" << std::endl;

	return 0;
}
