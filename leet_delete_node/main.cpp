#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

void deleteNode(ListNode* node) {
  node->val = node->next->val;
  node->next = node->next->next;
}

int main() {
  int nums[3]{5, 1, 9};

  ListNode *head = new ListNode(4);
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

  deleteNode(head->next);

  cur = head;
  while (cur) {
    cout << cur->val << " ";
    cur = cur->next;
  }
  cout << endl;

  return 0;
}