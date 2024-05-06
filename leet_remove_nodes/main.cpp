#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* setup(vector<int> nums) {
  ListNode* head = new ListNode(nums[0]);
  ListNode* cur = head;

  for (int i = 1; i < nums.size(); ++i) {
    cur->next = new ListNode(nums[i]);
    cur = cur->next;
  }

  return head;
}

ListNode* removeNodes(ListNode* head) {
  deque<ListNode*> dq;

  ListNode* cur = head;
  while (cur) {
    if (dq.empty()) {
      dq.push_back(cur);
    } else {
      while (!dq.empty() && dq.back()->val < cur->val) {
        dq.pop_back();
      }
      dq.push_back(cur);
    }
    cur = cur->next;
  }

  ListNode* new_head = dq.front();
  ListNode* new_cur = new_head;
  dq.pop_front();

  while (!dq.empty()) {
    new_cur->next = dq.front();
    new_cur = new_cur->next;
    dq.pop_front();
  }

  new_cur->next = nullptr;

  return new_head;
}

// [998,961,943,920,698]

int main() {
  vector<int> nums;

  int num = 0;
  while(cin >> num) {
    nums.push_back(num);
  }

  // for (int i = 0; i < nums.size(); ++i) {
  //   cout << nums[i] << " ";
  // }
  // cout << endl;

  ListNode* head = setup(nums);
  ListNode* cur = head;
  // while (cur) {
  //   cout << cur->val << " ";
  //   cur = cur->next;
  // }
  // cout << endl;
  head = removeNodes(head);

  while (head != nullptr) {
    cout << head->val << " ";
    head = head->next;
  }
  cout << endl;

  return 0;
}