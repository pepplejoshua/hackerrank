#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

/*
Assuming an array of size 5 with a window of 2:
3 4 6 3 4:

dq = []
for i = 0:
  dq = [0]

for i = 1:
  starts with dq = [0]
  but arr[dq.back()] (3) < arr[i] (4), so pop_back
  dq = [1]
  since i (1) >= 1 (k - 1 = 2 - 1 = 1), 
  print arr[1] (4) for this window

for i = 2:
  starts with dq = [1]
  since 1 is > i - k (2 - 2 = 0), we leave 1
  but arr[dq.back]
  
*/
void printKMax3(int arr[], int n, int k) {
  deque<int> dq;
  for (int i = 0; i < n; i++) {
    // remove elements from the front of deque that
    // are no longer within the current window
    while (!dq.empty() && dq.front() <= i - k) {
      dq.pop_front();
    }

    // remove elements from the back of deque that are
    // smaller than the current element
    while(!dq.empty() && arr[dq.back()] < arr[i]) {
      dq.pop_back();
    }

    dq.push_back(i);

    // print the maximum element if the window size is k
    if (i >= k-1) {
      cout << arr[dq.front()] << " ";
    }
  }
  cout << endl;
}

void printKMax2(int arr[], int n, int k){
  deque<int> dq(n);
  // load deque
	for (int i = 0; i < n; i++) {
    dq.push_back(arr[i]);
  }

  while (dq.size() >= k) {
    // collect the first k items and 
    auto m = max_element(dq.begin(), dq.begin()+k);
    cout << *m << " ";
    dq.pop_front();
  }
  cout << endl;
}

void printKMax(int arr[], int n, int k) {
  int start = 0;

  while (start + k <= n) {
    int *m = max_element(arr + start, arr + start + k);
    cout << *m << " ";
    start++;
  }
  cout << endl;
}

int main(){
	int t;
	cin >> t;
	while(t>0) {
		int n,k;
    	cin >> n >> k;
    	int i;
    	int arr[n];
    	for(i=0;i<n;i++)
      		cin >> arr[i];
    	printKMax3(arr, n, k);
    	t--;
  	}
  	return 0;
}