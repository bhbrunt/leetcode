#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

class Solution {
	private:
		int n;

		std::mutex m;
		std::condition_variable cv;

		int state = 0;

	public:
		Solution(int n) {
			this->n = n;
		}

		void foo() {
			for (int i = 0; i < n; i++) {
				std::unique_lock<std::mutex> lck(m);
				cv.wait(lck, [this]{return state == 0;});
				std::cout << "foo";
				state = 1;
				cv.notify_all();
			}
		}

		void bar() {
			for (int i = 0; i < n; i++) {
				std::unique_lock<std::mutex> lck(m);
				cv.wait(lck, [this]{return state == 1;});
				std::cout << "bar";
				state = 0;
				cv.notify_all();
			}
			std::cout << std::endl;
		}

};

int main() {
	Solution solution(4);
	auto start = std::chrono::high_resolution_clock::now();
	std::thread threadA(&Solution::foo, &solution);
	std::thread threadB(&Solution::bar, &solution);

	threadA.join();
	threadB.join();

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Duration: " << duration.count() << " ms" << std::endl;

	return 0;
}
