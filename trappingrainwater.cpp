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
		for (int l = i; l < v.size(); l++)
			leftMax = max(leftMax, v[l]);
		for (int r = i; r >= 0; r--)
			rightMax = max(rightMax, v[r]);

		int lvl = min(leftMax, rightMax);
		total += max(0, lvl - v[i]);
	}
	return total;
}

// Method 2:- Precompute Prefix Max and Suffix Max
// Instead of calculating leftMax and rightMax for all steps, just precompute and store it once
// Rest of the steps are similar to Method 1

// Time Complexity: O(N) since we only need to calculate max(s) once
// Space Complexity: O(N) since extra space needed for suffix/prefix arrays

int trappingRainwater2(vector<int>& v) {
	int N = v.size(), total = 0;
	vector<int> prefixMax(N, 0), suffixMax(N, 0);
	prefixMax[0] = v[0], suffixMax[N - 1] = v[N - 1];
	for (int i = 1; i < N; i++)
		prefixMax[i] = max(v[i], prefixMax[i - 1]);
	for (int j = N - 2; j >= 0; j--)
		suffixMax[j] = max(v[j], suffixMax[j + 1]);

	for (int i = 0; i < v.size(); i++) {
		int leftMax = prefixMax[i], rightMax = suffixMax[i];
		int level = min(leftMax, rightMax);
		total += max(0, level - v[i]);
	}
	return total;
}

// Method 3:- Two Pointer Approach with Lower Envelope Technique
// Need to figure out min(max[0, i], max[i, N-1]) for each i without using O(N) space or time
// max[0, i] is the leftMax for i; max[i, N-1] is the rightMax for i; Plot their functions for clarity
// We can figure out leftMax(i) on the go, but rightMax(i) requires an iteration from i to N-1
// We can use a second pointer from N-1 to 0 to figure out max[j, N-1] on the go ie. rightMax for j
// Using leftMax(i) and rightMax(j), we can figure out g(i) = min(max[0, i], max[i, N-1]) ie. lower envelope
// In [0, N-1], Prefix Max (leftMax()) is monotinically increasing, Suffix Max (rightMax()) is monotonically decreasing
// If rightMax(j) >= leftMax(i), g(i) = leftMax(i) since rightMax(i) >= rightMax(j) due to monotoncity of rightMax()
// We can then use this value for g(i) to figure out water level for v[i] to add to the total, and then move i++ ahead
// If leftMax(i) > rightMax(j), g(j) = rightMax(j) since leftMax(j) >= leftMax(i) due to monotonicity of leftMax()
// We can then use this value for g(j) to figure out water level for v[j] to add to the total, and then move j-- ahead
// Finally, when i and j cross over, we will have calculated the value for all indices in the elevation map v[]

// Time Complexity: O(N) for covering all the elements of the array once
// Space Complexity: O(1) since no extra data structure needed

int trappingRainwater(vector<int>& v) {
	int left = 0, right = v.size() - 1;            // Two pointers (left for i, right for j) to move and cover the array
	int leftMax = v[left], rightMax = v[right];    // leftMax: curr. max from left; rightMax: curr. max from right
	int total = 0;                                 // Minmax ie. min(leftMax, rightMax) is the lower envelope function
	while (left <= right) {                        // While the two pointers do not cross each other..
		leftMax = max(leftMax, v[left]);           // Update the current leftMax if curr. v[left] > leftMax
		rightMax = max(rightMax, v[right]);        // Update the current rightMax if curr. v[right] > rightMax
		if (leftMax <= rightMax) {                 // min(leftMax, rightMax) is leftMax since rightMax can only increase on right--
			total += max(0, leftMax - v[left]);    // leftMax == min(leftMax, rightMax) as well since leftMax <= rightMax
			left++;                                // Move left while leftMax <= rightMax till we find a leftMax > rightMax
		}                                          // right stays fixed for if{} so if v[left] > rightMax, we switch to moving right
		else {                                     // min(leftMax, rightMax) is rightMax since leftMax can only increase on left++
			total += max(0, rightMax - v[right]);  // rightMax == min(leftMax, rightMax) as well since leftMax > rightMax
			right--;                               // Move right while leftMax > rightMax till we find a rightMax >= leftMax
		}                                          // left stays fixed for else{} so if v[right] > leftMax, we switch to moving left
	}                                              // Due to if(), no need to know both leftMax and rightMax as we know their min()
	return total;
}

// Method 4:- Two Pointers Approach (Fastest) - pointers to find the closest global/local peaks
// 1. Start with a total equal to 0
// 2. Find first peak from the left (leftMax)
// 3. Find the closest peak to the right of leftMax (rightMax)
// 4. If rightMax >= leftMax, it is sufficient to find water levels so break the search loop
// 5. Run a loop from leftMax to rightMax and add max(0, min(leftMax,rightMax) - v[x]) to the total
// 6. If rightMax < leftMax, store it for now (tempPeak) but continue looking for a rightMax >= leftMax
// 7. While looking, if you encounter a rightMax < leftMax but rightMax > tempPeak, update tempPeak and rightMax
// 8. If a better rightMax found by the end, go with it else use the current rightMax only
// 9. Implement a unique check for the last element (it could be a peak as well)
// 10. Update leftMax to be equal to current rightMax for the next iteration from rightMax to newRightMax
// 11. If leftMax == rightMax at any point, the search has struck a local minima and gotten stuck so break it

// Time Complexity: O(N) since all elements visited twice at max
// Space Complexity: O(1) since no extra data structure used

int trappingRainwater4(vector<int>& v) {
	int total = 0, leftMax = 0, x = 0;
	for (int i = 1; i < v.size(); i++) {
		if (v[0] < v[1] && v[i] >= v[i + 1] && v[i] > v[i - 1]) {
			leftMax = i;
			break;
		}
	}

	while (x != v.size()) {
		int rightMax = leftMax, tempPeak = 0;

		for (int j = leftMax + 1; j < v.size(); j++) {
			if (j == v.size() - 1) {
				if (v[j] > v[j - 1] && v[j] > tempPeak) {
					rightMax = j;
					break;
				}
			}
			else if (v[leftMax] > v[j] && v[j] >= v[j + 1] && v[j] > v[j - 1] && v[j] > tempPeak) {
				rightMax = j;
				tempPeak = v[j];
				continue;
			}
			else if (v[j] >= v[leftMax] && v[j] >= v[j + 1] && v[j] > v[j - 1]) {
				rightMax = j;
				break;
			}
		}

		int lvl = min(v[leftMax], v[rightMax]);
		x = leftMax + 1;
		while (x < rightMax)
			total += max(0, lvl - v[x++]);

		if (leftMax == rightMax)
			break;

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

// 9
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
// 6
// 4 4 4 7 1 0
// 8
// 0 1 1 1 1 1 2 1

// Outputs:

// 0
// 3
// 3
// 8
// 9
// 6
// 10
// 0
// 0
