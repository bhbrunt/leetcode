#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

class Solution {
	public:
		void first() {
			std::unique_lock<std::mutex> lck(m);
			std::cout << "first" << std::endl;
			first_executed = true;
			cv.notify_all();
		}

		void second() {
			std::unique_lock<std::mutex> lck(m);
			while (!first_executed) cv.wait(lck);
			std::cout << "second" << std::endl;
			second_executed = true;
			cv.notify_all();
		}

		void third() {
			std::unique_lock<std::mutex> lck(m);
			while (!second_executed) cv.wait(lck);
			std::cout << "third" << std::endl;
		}

	private:
		std::mutex m;
		std::condition_variable cv;

		bool first_executed = false;
		bool second_executed = false;
};

void printFirst() {
}

int main() {
	Solution solution;
	auto start = std::chrono::high_resolution_clock::now();
	std::thread threadC(&Solution::third, &solution);
	std::thread threadB(&Solution::second, &solution);
	std::thread threadA(&Solution::first, &solution);

	threadA.join();
	threadB.join();
	threadC.join();

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Duration: " << duration.count() << " ms" << std::endl;

	return 0;
}
