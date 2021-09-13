#include <bits/stdc++.h>
using namespace std;

// Constraints:-
// 0 <= Length <= 3 * 10^4
// -100 <= v[i] <= 100
// v is sorted in non-descending order

// Method 1:- Two Pointers Technique
// Using Location Pointer i to iterate over the sorted array and check for unique elements
// Using Partition Pointer K and shifting newly encountered unique values to v[K]
// Time Complexity: O(N), Space Complexity: O(1)

int removeDuplicates1(vector<int>& v) {
	if (v.empty())
		return 0;

	int k = 0;
	for (int i = 1; i < v.size(); i++) {
		if (v[i] != v[i - 1]) {
			k++;
			v[k] = v[i];
		}
	}
	return k + 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int testNum;
	cin >> testNum;
	while (testNum--) {
		int size;
		cin >> size;
		vector<int> v;
		for (int i = 0; i < size; i++) {
			int ele;
			cin >> ele;
			v.push_back(ele);
		}

		int k = removeDuplicates(v);
		cout << k << endl;
		for (int i = 0; i < k; i++)
			cout << v[i] << " ";
		cout << endl;
	}
	return 0;
}

// Testcases:-

// Inputs:

// 5
// 0

// 3
// 1 1 2
// 10
// 0 0 1 1 1 2 2 3 3 4
// 1
// 17
// 2
// 1 2

// Outputs:

// 0

// 2
// 1 2
// 5
// 0 1 2 3 4
// 1
// 17
// 2
// 1 2
