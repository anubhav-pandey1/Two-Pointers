#include <bits/stdc++.h>
using namespace std;

// Constraints:-
// 1 <= Length <= 2 x 10^4; so it must be O(NlogN) or O(N)
// 0 <= a[i] <= 10^5

// Method 1:- Brute force: Calculate water level for each cell
// At any cell, water height = min. of (max height towards its left, max height towards its right)
// These need not be closest, local maximas but global maximas towards left and right
// Time complexity: O(N^2), Space complexity: O(1)

int trappingRainwater1(vector<int>& v) {
	int total = 0;
	for (int i = 0; i < v.size(); i++) {
		int leftMax = 0, rightMax = 0;
		for (int l = i; l >= 0; l--)
			leftMax = max(leftMax, v[l]);
		for (int r = i; r < v.size(); r++)
			rightMax = max(rightMax, v[r]);

		int lvl = min(leftMax, rightMax);
		total += max(0, lvl - v[i]);
	}
	return total;
}

// Method 2:- Two Pointers Approach

int trappingRainwater(vector<int>& v) {
	int total = 0;

	int leftMax = 0;

	while (leftMax < v.size()) {
		for (int i = leftMax + 1; i < v.size(); i++) {
			if (v[0] < v[1] && v[i] >= v[i + 1] && v[i] > v[i - 1]) {
				leftMax = i;
				break;
			}
		}

		int rightMax = 0;
		for (int j = leftMax + 1; j < v.size(); j++) {
			if (v[leftMax] > v[j] && v[j] >= v[j + 1] && v[j] > v[j - 1]) {
				rightMax = j;
				continue;
			}
			if (v[j] >= v[leftMax]) {
				rightMax = j;
				break;
			}
		}

		int lvl = min(v[leftMax], v[rightMax]);
		for (int x = leftMax + 1; x < rightMax; x++) {
			total += max(0, lvl - v[x]);
		}

		leftMax = rightMax;
	}
	return total;
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

		cout << trappingRainwater(v) << endl;
	}
	return 0;
}

// Incorrect approach based on finding closest local peaks:
// Identify potential local peaks and find water volume between peaks
// Doesn't work for [4,2,0,3,2,4,3,4] as global peaks at [0] and [5] overshadow local peak at [3]

// int trappingRainwater(vector<int>& v) {
// 	vector<int> peaks;
// 	if (v.size() > 1) {
// 		if (v[0] >= v[1])
// 			peaks.push_back(0);
// 		for (int i = 1; i < v.size() - 1; i++)
// 			if ((v[i] >= v[i + 1] && v[i] > v[i - 1]))   // Gets local peaks only
// 				peaks.push_back(i);
// 		if (v[v.size() - 1] > v[v.size() - 2])
// 			peaks.push_back(v.size() - 1);
// 	}
// 	else {
// 		return 0;
// 	}

// 	int total = 0;
// 	for (int i = 0; i < peaks.size() - 1; i++) {
// 		int j = i + 1, currSum = 0;
// 		for (int x = peaks[i] + 1; x < peaks[j]; x++) {
// 			int lvl = min(v[peaks[i]], v[peaks[j]]);
// 			currSum += max(0, lvl - v[x]);
// 		}
// 		total += currSum;
// 	}
// 	return total;
// }

// Testcases:-

// Inputs:

// 7
// 1
// 0
// 4
// 2 1 0 2
// 9
// 0 1 0 2 1 2 1 0 1
// 12
// 0 4 3 2 1 5 6 4 2 3 0 1
// 6
// 4 2 0 3 2 5
// 12
// 0 1 0 2 1 0 1 3 2 1 2 1
// 8
// 4 2 0 3 2 4 3 4

// Outputs:

// 0
// 3
// 3
// 8
// 9
// 6
// 10
