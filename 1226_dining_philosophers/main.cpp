#include <iostream>
#include <functional>
#include <sstream>
#include <thread>
#include <mutex>
#include <chrono>

class Solution {
	public:
		const static int n = 5;

		void wantsToEat(int philosopher) {

			const int left_fork = philosopher % n;
			const int right_fork = (philosopher + 1) % n;
			std::scoped_lock<std::mutex, std::mutex> both_forks_lock(m_forks[left_fork], m_forks[right_fork]);

			pickLeftFork(philosopher);
			pickRightFork(philosopher);

			eat(philosopher);

			putLeftFork(philosopher);
			putRightFork(philosopher);

		}

	private:
		std::array<std::mutex, n> m_forks;

		void pickLeftFork(int philosopher) {
			std::stringstream s;
			s << "Philosopher " << philosopher << " picks up fork " << philosopher%n << std::endl;
			std::cout << s.str();
		}

		void pickRightFork(int philosopher) {
			std::stringstream s;
			s << "Philosopher " << philosopher << " picks up fork " << (philosopher+1)%n << std::endl;
			std::cout << s.str();
		}
		void eat(int philosopher) {
			std::stringstream s;
			s << "Philosopher " << philosopher << " is eating." << std::endl;
			std::cout << s.str();
		}

		void putLeftFork(int philosopher) {
			std::stringstream s;
			s << "Philosopher " << philosopher << " puts down fork " << philosopher%n << std::endl;
			std::cout << s.str();
		}

		void putRightFork(int philosopher) {
			std::stringstream s;
			s << "Philosopher " << philosopher << " puts down fork " << (philosopher+1)%n << std::endl;
			std::cout << s.str();
		}
};

int main() {
	Solution solution;
	std::vector<std::unique_ptr<std::thread>> threads;
	auto start = std::chrono::high_resolution_clock::now();
	for (size_t i=0; i<solution.n; i++) {
		std::unique_ptr<std::thread> ptr(new std::thread(&Solution::wantsToEat, &solution, i));
		threads.push_back(std::move(ptr));
	}

	for (auto& thread : threads) {
		thread->join();
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Duration: " << duration.count() << " ms" << std::endl;

	return 0;
}
