#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

class Solution {
	private:
		int n;
		int counter = 1;

		std::mutex m;
		std::condition_variable cv;

		void printFizz() {
			std::cout << "Fizz" << std::endl;
		}

		void printBuzz() {
			std::cout << "Buzz" << std::endl;
		}

		void printFizzBuzz() {
			std::cout << "FizzBuzz" << std::endl;
		}

		void printNumber(int n) {
			std::cout << n << std::endl;
		}

	public:
		Solution(int n) {
			this->n = n;
		}

		void run(std::function<bool(int)> testFn, std::function<void(int)> printFn) {
			while (true) {
				std::unique_lock<std::mutex> lck(m);
				cv.wait(lck, [this, testFn]{return ((counter > n) || testFn(counter)); });
				if (counter > n) return;
				printFn(counter);
				counter++;
				cv.notify_all();
			}
		}

		// printFizz() outputs "fizz".
		void fizz() {
			run([](int counter){return ((counter % 3 == 0) && !(counter % 15 == 0)); },
					[&](int){ printFizz(); } );
		}

		// printBuzz() outputs "buzz".
		void buzz() {
			run([](int counter){return ((counter % 5 == 0) && !(counter % 15 == 0)); },
					[&](int){ printBuzz(); } );
		}

		// printFizzBuzz() outputs "fizzbuzz".
		void fizzbuzz() {
			run([](int counter){return (counter % 15 == 0); },
					[&](int){ printFizzBuzz(); } );
		}

		// printNumber(x) outputs "x", where x is an integer.
		void number() {
			run([](int counter){return (!(counter % 3 == 0) && !(counter % 5 == 0)); },
					[&](int i){ printNumber(i); } );
		}
};

int main() {
	Solution solution(15);
	auto start = std::chrono::high_resolution_clock::now();
	std::thread threadFizz(&Solution::fizz, &solution);
	std::thread threadBuzz(&Solution::buzz, &solution);
	std::thread threadFizzBuzz(&Solution::fizzbuzz, &solution);
	std::thread threadNumber(&Solution::number, &solution);

	threadFizz.join();
	threadBuzz.join();
	threadFizzBuzz.join();
	threadNumber.join();

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Duration: " << duration.count() << " ms" << std::endl;

	return 0;
}
