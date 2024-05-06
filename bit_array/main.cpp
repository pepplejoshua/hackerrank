#include <iostream>
#include <unordered_set>
 
using namespace std;

int main() {
  int N, P, Q;
  long long int S;

  // Read input
  cin >> N >> S >> P >> Q;

  // Use unordered_set to store unique elements
  unordered_set<long long int> seen;

  // Calculate initial value modulo 2^31 for overflow handling
  S %= (1LL << 31);

  // Add initial value to the set
  seen.insert(S);

  // Loop to calculate and store distinct sequence values
  for (int i = 1; i < N; ++i) {
    // Calculate next value
    S = (S * P + Q) % (1LL << 31);
    // Insert only if not already present (ensures uniqueness)
    seen.insert(S);
  }

  // Print the number of distinct elements (set size)
  cout << seen.size() << endl;

  return 0;
}
