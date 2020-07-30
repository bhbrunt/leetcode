#include <vector>
#include <iostream>
#include <chrono>
#include <cassert>

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	~ListNode() {delete next;}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
	public:
		bool isPalindrome(ListNode* head) {
			if (!head) return true;

			// Reverse the list and compare. O(n) time with O(n) extra space.
			ListNode* rhead = nullptr;
			ListNode* current = head;
			while (current != nullptr) {
				rhead = new ListNode(current->val, rhead);
				current = current->next;
			}

			current = head;
			ListNode* rcurrent = rhead;
			while (current != nullptr) {
				if (current->val != rcurrent->val) return false;
				current  = current->next;
				rcurrent = rcurrent->next;
			}

			delete rhead;

			return true;
		}
};

int main() {
	const std::vector<int> test_case = {1,2,3,4,4,3,2,1};
	ListNode* head(nullptr);
	for (auto i=test_case.rbegin(); i<test_case.rend(); ++i) {
		head = new ListNode(*i, head);
	}

	Solution solution;
	auto start = std::chrono::high_resolution_clock::now();
	bool output = solution.isPalindrome(head);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Output = " << output << std::endl;
	std::cout << "Duration: " << duration.count() << " ms" << std::endl;
	assert(output == true);

	delete head;

	return 0;
}
