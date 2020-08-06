#include <vector>
#include <climits>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <cassert>

class Solution {
	public:
		int threeSumClosest(std::vector<int>& nums, int target) {
			std::sort(nums.begin(), nums.end());

			int min_dist(INT_MAX);
			for (size_t i=0; i<nums.size()-2; i++) {
				const int remaining = nums[i] - target;

				size_t j(i+1), k(nums.size()-1);
				while (j<k) {
					const int dist = remaining + nums[j] + nums[k];
					if (abs(dist) < abs(min_dist)) min_dist = dist;

					if (dist < 0) j++;
					else if (dist > 0) k--;
					else break; // dist == 0
				}
			}
			return min_dist + target;
		}
};

int main() {
	std::vector<int> test_case = {82,-16,-60,-48,32,-30,0,-89,70,-46,-82,-58,66,41,-96,-55,-49,-87,-33,-65,9,14,81,-11,80,-93,79,-63,-61,-16,22,-31,75,12,17,-6,37,-2,-89,-66,3,-95,-74,58,-95,22,11,-20,-36,60,-75,46,-52,-61,-28,7,-50,-45,93,-91,-43,35,-99,-39,53,-54,-98,-4,13,-90,23,-4,-65,29,85,-76,-64,81,32,-97,51,12,-82,-31,81,-2,-83,-9,89,-37,-23,-66,-91,-15,-98,-74,94,30,-2,-70,13,19,-77,-42,33,-70,25,77,47,-70,-70,60,-63,-4,83,13,-78,-23,28,-86,-11,-16,-57,-84,51,-48,-63,-15,29,56,-25,73,-69,23,28,90,96,41,65,-22,-43,-68,-77,31,69,-84,23,-63,-18,20,-93,-17,-48,-73,14,-95,98,-64,-12,-45,14,7,51,-61,89,-48,-23,2,-56,84,-2,27,74,-39,-18,-65,79,-36,-76,-30,44,78,-76,37,88,0,32,55,-51,23,-9,68,26,15,66,66,-56,-42,56,28,33,-32,-23,-36,-12,-76,-12,42,12,40,69,54,82,-22,-7,46,-46};
	const int target = 270;

	Solution solution;
	auto start = std::chrono::high_resolution_clock::now();
	int output = solution.threeSumClosest(test_case, target);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Output = " << output << std::endl;
	std::cout << "Duration: " << duration.count() << " ms" << std::endl;

	assert(output == 270);

	return 0;
}
