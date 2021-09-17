#include <bits/stdc++.h>
using namespace std;

// Constraints:-
// 1 <= Length <= 3*10^4
// -10^5 <= v[i] <= 10^5
// Find the contiguous subarray with the largest sum and return the sum

// Method 1:- Two Pointers ie. Prefix-sum max, Suffix-sum max approach:
// Works for almost all the cases except when either all prefix sums or suffix sums are negative
// The max sum subarray lies between [i, j] where i is the index of max prefix sum and j for max suffix sum
// Time complexity: O(N)
// Space complexity: O(1)

int maxSubarraySum1(vector<int>& v) {
	int len = v.size();
	int maxi = 0, currSumLeft = 0, prefixMax = 0;
	for (int i = 0; i < len; i++) {
		currSumLeft += v[i];
		if (currSumLeft > prefixMax) {
			prefixMax = currSumLeft;
			maxi = i;
		}
	}

	int maxj = len - 1, currSumRight = 0, suffixMax = 0;
	for (int j = len - 1; j >= 0; j--) {
		currSumRight += v[j];
		if (currSumRight > suffixMax) {
			suffixMax = currSumRight;
			maxj = j;
		}
	}

	int currSum = 0;
	for (int x = min(maxi, maxj); x <= max(maxi, maxj); x++) {
		currSum += v[x];
	}

	return currSum;
}

// Method 2:- Kadane's Algorithm
// For each v[i], we find the max subarray sum till i-1 and use it to solve for i
// We carry forward a subarray sum as long as it gives us a positive sum ie. does not reduce sum
// We change sum to be 0 if it turns out to be negative (after calculating maxSum) for a subarray
// We start maxSum = INT_MIN and not 0 so that if v[0] < 0, we still get maxSum = v[0]
// We can declare maxSum = v[0] as well to achieve the same thing
// Essentially, we're finding the optimal answer for each i and using it to solve for i+1 and globally
// This is very similar to dynamic programming ie. subproblems and global optimization
// Time complexity: O(N)
// Space complexity: O(1)

int maxSubarraySum(vector<int>& v) {
	int sum = 0, maxSum = INT_MIN;
	for (int i = 0; i < v.size(); i++) {
		sum += v[i];
		maxSum = max(sum, maxSum);
		sum = max(0, sum);
	}
	return maxSum;
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

		cout << maxSubarraySum(v) << endl;
	}
	return 0;
}

// Testcases:-

// Inputs:

// 6
// 9
// -2 1 -3 4 -1 2 1 -5 4
// 1
// 1
// 5
// 5 4 -1 7 8
// 8
// -2 -3 4 -1 -2 1 5 -3
// 2
// -2 1
// 2
// -2 -1

// Outputs:

// 6
// 1
// 23
// 7
// 1
// -1
