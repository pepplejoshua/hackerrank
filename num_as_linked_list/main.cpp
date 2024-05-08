#include <iostream>
#include <deque>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *multiplyBy(ListNode *head, int by) {
  deque<int> nums;
  ListNode *cur = head;

  while (cur) {
    nums.push_back(cur->val);
    cur = cur->next;
  }

  int carry = 0;
  for (int i = nums.size() - 1; i >= 0; --i) {
    int product = nums[i] * by + carry;
    nums[i] = product % 10;
    carry = product / 10;
  }

  if (carry) {
    nums.push_front(carry);
  }

  ListNode *newHead = new ListNode(nums.front());
  cur = newHead;
  for (int i = 1; i < nums.size(); ++i) {
    cur->next = new ListNode(nums[i]);
    cur = cur->next;
  }

  return newHead;
}

int main() {
  int nums[2]{7, 7};
  ListNode *head = new ListNode(2);
  ListNode *cur = head;

  for (int n : nums) {
    cur->next = new ListNode(n);
    cur = cur->next;
  }

  cur = head;
  while (cur) {
    cout << cur->val << " ";
    cur = cur->next;
  }
  cout << endl;

  ListNode *newHead = multiplyBy(head, 8);

  cur = newHead;
  while (cur) {
    cout << cur->val << " ";
    cur = cur->next;
  }
  cout << endl;

  return 0;
}