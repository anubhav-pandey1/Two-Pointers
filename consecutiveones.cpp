#include <bits/stdc++.h>
using namespace std;

// Constraints:-
// 1 <= Length <= 10^5
// v[] is a binary array with 0's and 1's

int maxConsecutiveOnes(vector<int>& v) {
	int maxCount = 0, currCount = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == 1) {
			currCount++;
			maxCount = max(maxCount, currCount);
		}
		else {
			currCount = 0;
		}
	}
	return maxCount;
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

		cout << maxConsecutiveOnes(v) << endl;
	}
	return 0;
}

// Testcases:-

// Inputs:

// 4
// 6
// 1 1 0 1 1 1
// 6
// 1 0 1 1 0 1
// 1
// 0
// 1
// 1

// Outputs:

// 3
// 2
// 0
// 1
