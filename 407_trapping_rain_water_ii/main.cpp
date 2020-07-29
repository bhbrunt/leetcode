#include <vector>
#include <queue>
#include <iostream>
#include <chrono>
#include <cassert>

typedef std::pair<int, int> HeightIndexPair;

class Solution {
public:
    int trapRainWater(std::vector<std::vector<int>>& heightMap) {
      if (heightMap.size() == 0) return 0;
      if (heightMap.at(0).size() == 0) return 0;

      const size_t N(heightMap.size());
      const size_t M(heightMap.at(0).size());

      std::vector<std::vector<bool>> visited(N, std::vector<bool>(M, false));
      std::priority_queue<HeightIndexPair, std::vector<HeightIndexPair>, std::greater<HeightIndexPair>> queue;

      // Add the boundary of the grid to the queue.
      for (size_t i=0; i<N; i++) {
        queue.push(std::make_pair(heightMap[i][0], i));
        queue.push(std::make_pair(heightMap[i][M-1], (M-1)*N + i));
        visited[i][0] = true;
        visited[i][M-1] = true;
      }
      for (size_t j=1; j<M-1; j++) {
        queue.push(std::make_pair(heightMap[0][j], j*N));
        queue.push(std::make_pair(heightMap[N-1][j], (j+1)*N - 1));
        visited[0][j] = true;
        visited[N-1][j] = true;
      }

      const std::vector<std::vector<int>> dirs = {{0,-1}, {0,1}, {-1,0}, {1,0}};

      int water_trapped(0);
      while (!queue.empty()) {
        auto point = queue.top(); queue.pop();
        const size_t i_point(point.second % N);
        const size_t j_point(point.second / N);
        const int height(point.first);

        for (const auto& dir : dirs) {
          const int i_neighbour(i_point + dir[0]);
          const int j_neighbour(j_point + dir[1]);
          if (i_neighbour < 0 || i_neighbour >= N) continue;
          if (j_neighbour < 0 || j_neighbour >= M) continue;
          if (visited[i_neighbour][j_neighbour]) continue;

          const int height_neighbour = heightMap[i_neighbour][j_neighbour];
          if (height_neighbour < height) {
            water_trapped += height - height_neighbour;
          }

          queue.push(std::make_pair(std::max(height, height_neighbour), j_neighbour*N + i_neighbour));
          visited[i_neighbour][j_neighbour] = true;
        }
      }
      return water_trapped;
    }
};

int main() {
	std::vector<std::vector<int>> test_case = { {1,4,3,1,3,2}, {3,2,1,3,2,4}, {2,3,3,2,3,1} };

	Solution solution;
	auto start = std::chrono::high_resolution_clock::now();
	int output = solution.trapRainWater(test_case);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Output = " << output << std::endl;
	std::cout << "Duration: " << duration.count() << " ms" << std::endl;

	assert(output == 4);

	return 0;
}
