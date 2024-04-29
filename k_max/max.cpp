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
  print arr[dq.front()] (4) for this window

for i = 2:
  starts with dq = [1]
  since dq.front() (1) > i - k (2 - 2 = 0), we leave 1
  but arr[dq.back()] (4) < arr[i] (6), so pop_back
  dq = [2]
  since i (2) >= 1 (k - 1 = 2 - 1 = 1),
  print arr[dq.front()] (6) for this window

for i = 3:
  starts with dq = [2]
  since dq.front() (2) > i - k (3 - 2 = 1), we leave 2 (still in window)
  arr[dq.back()] (6) > arr[i] (3), so no pop_back
  dq = [2, 3]
  since i (3) >= 1 (k - 1 = 2 - 1, 1),
  print arr[dq.front()] (6) for this window

for i = 4:
  starts with dq = [2, 3]
  since dq.front() (2) == (!>) i - k (4 - 2 = 2), we pop 2
  but arr[dq.back()] (3) < arr[i] (4), so pop_back
  dq = [4]
  since i (4) >= 1 (k - 1 = 2 - 1, 1),
  print arr[dq.front()] (4) for this window
  
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

// worst performing since we first load all the array elements
// into deque before doing any actual work instead of using it
// to hold and filter out array elements by lifetime (i.e, is it
// in i - k range, since i will be the index of last element in the
// array) as well as size (we remove things smaller than the current
// element, making sure only the biggest element is at the front)
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

// second fastest behind printKMax3 since it does not load up
// deque like printKMax3, otherwise it uses the same naive approach
// of actually comparing elements vs what seems like casually filtering
// using deque in printKMax3
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