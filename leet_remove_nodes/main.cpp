#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNodes(ListNode* head) {
        
    }
};

ListNode* setup(vector<int> nums) {
  ListNode *node = new ListNode;
  node->val = nums[0];
  ListNode *head = node;

  for (int i = 1; i < nums.size(); ++i) {

  }
  return head;
}

int main() {
  vector<int> nums;

  int num = 0;
  while(cin >> num) {
    nums.push_back(num);
  }

  Solution().removeNodes(setup(nums));
  return 0;
}