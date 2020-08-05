#include <iostream>
#include <vector>
#include <chrono>

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
	public:
		ListNode* removeElements(ListNode* head, int val) {
			if (head == nullptr) return nullptr;
			head->next = removeElements(head->next, val);
			if (head->val == val) {
				ListNode* old_head = head;
				head = head->next;
				delete old_head;
			}
			return head;
		}
};

int main() {
	const std::vector<int> test_case = {1, 2, 6, 3, 4, 5, 6};
	ListNode* head(nullptr);
	ListNode* curr(nullptr);
	for (const int i : test_case) {
		ListNode* n = new ListNode(i);
		if (!head) {
			head = curr = n;
		} else {
			curr->next = n;
			curr = curr->next;
		}
	}

	Solution solution;
	auto start = std::chrono::high_resolution_clock::now();
	ListNode* output = solution.removeElements(head, 6);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Output = ";
	curr = output;
	while (curr != nullptr) {
		std::cout << curr->val << " ";
		curr = curr->next;
	}
	std::cout << std::endl;
	std::cout << "Duration: " << duration.count() << " ms" << std::endl;

	curr = output;
	while (curr != nullptr) {
		ListNode* old = curr;
		curr = curr->next;
		delete old;
	}

	return 0;
}
