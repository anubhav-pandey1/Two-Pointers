#include <bits/stdc++.h>
using namespace std;

// Constraints:-
// Length <= 3 x 10^3 => O(N^2)
// -10^5 <= a[i] <= a[i]

// Method 1:- Hashing
// Use a set of vectors to store the triplets so that only unique triplets are stored.
// We can't use an unordered set as an unordered set can't be transformed to a vector or iterated over (no order)
// Create a frequency hashmap to store the frequencies of all array elements
// v[i] + v[j] + X = target, so we must iterate using two loops to try to find X for each v[i] and v[j]
// Reduce frequency of v[i] and v[j] initially so as to avoid counting them as candidates for X
// Check if there exists a suitable X in the map/array for the given v[i] and v[j] (use of hashing)
// Increase the frequency of v[i] and v[j] back again once done with the check in the map
// Keep sorting (to avoid duplicates) and storing triplets as and when you encounter
// Time complexity => O(N^2 * log M), log M for insertion in set where M is the size of the set
// Space complexity => O(M) + O(N), for the set of vectors as well as for the hashmap

vector<vector<int>> threeSumHash(vector<int>& v, int K) {
	set<vector<int>> triplets;
	unordered_map<int, int> mp;
	for (int i = 0; i < v.size(); i++)
		mp[v[i]]++;

	for (int i = 0; i < v.size(); i++) {
		mp[v[i]]--;
		for (int j = i + 1; j < v.size(); j++) {
			mp[v[j]]--;
			if (mp.find(K - v[i] - v[j]) != mp.end() && mp[K - v[i] - v[j]] > 0) {
				vector<int> triplet = {v[i], K - v[i] - v[j], v[j]};
				sort(triplet.begin(), triplet.end());
				triplets.insert(triplet);
			}
			mp[v[j]]++;
		}
		mp[v[i]]++;
	}
	return vector<vector<int>> (triplets.begin(), triplets.end());
}

// Method 2:- Two Pointers
// Sort the array since we don't need to return indices, only values -> Two Pointers approach can be used
// a + b + c = K, we will fix a and find (b,c) using the Two Pointers approach
// To avoid using a set (and extra O(M) space), we will jump over duplicates for a/b/c
// We will jump over duplicates of a (fix) only after the Two Pointer stuff is complete for that a so that..
// ..we don't miss cases where b or c take up a value equal to the duplicate of a (duplicates are adjacent in sorted arrays)
// We will jump over duplicates of (b,c) only when we find a triplet (a,b,c) as it is only needed to avoid duplicate answers

vector<vector<int>> threeSum(vector<int>& v, int K) {
	vector<vector<int>> triplets;
	sort(v.begin(), v.end());
	for (int fix = 0; fix < v.size(); fix++) {                                   // Iterate over all possible values of a/fix
		int left = fix + 1, right = v.size() - 1, target = K - v[fix];           // Define the initial states of the two pointers and the target
		while (left < right) {                                                   // Two Pointer stuff gets over when left-ptr goes beyond right-ptr
			if (v[left] + v[right] == target) {                                  // Triplet found
				triplets.push_back({v[fix], v[left], v[right]});                 // Storing the triplet
				while (left < right && v[right] == v[right - 1]) right--;        // Jump over duplicates of right till the last duplicate value (1 more jump needed)
				while (left < right && v[left] == v[left + 1]) left++;           // Jump over duplicates of left till the last duplicate value (1 more jump needed)
				left++, right--;                                                 // Go to the next value which is not the same as the prev. left and right
			}                                                                    // ^This line also needed for cases when there are no duplicates
			else if (v[left] + v[right] > target)                                // If curr. sum exceeds target, we need to reduce it
				// while (right > 0 && v[right] == v[right - 1]) right--;        // Not needed but we can jump over all but 1 duplicates of right to get to the last duplicate value
				right--;                                                         // Reduce curr. sum by reducing the larger value of the (left, right) pair
			else if (v[left] + v[right] < target)                                // If curr. sum is less than the target, we need to increase it
				// while (left < v.size() - 1 && v[left] == v[left + 1]) left++; // Not needed but we can jump over all but 1 duplicates of left to get to the last duplicate value
				left++;                                                          // Increase curr. sum by increasing the larger value of the (left, right) pair
		}
		while (fix + 1 < v.size() && v[fix + 1] == v[fix]) fix++;                // Jumping over duplicates of fix/a only after 2-ptr stuff is complete
	}                                                                            // ^so that we can avoid on missing out on cases where (a, a, a) is the answer
	return triplets;
}

// Time complexity => O(N^2), Auxiliary Space complexity => O(1)

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
		int target, size;
		cin >> target >> size;
		vector<int> v;
		for (int i = 0; i < size; i++) {
			int ele;
			cin >> ele;
			v.push_back(ele);
		}

		vector<vector<int>> result = threeSum(v, target);
		for (auto res : result) {
			for (int x : res)
				cout << x << " ";
			cout << endl;
		}
		cout << "__________" << endl;
	}
	return 0;
}

// Greedy optimization will not work:-
// Counter case is [3, 2, 4] for target = 6
// It gets stuck on i = 0 and j oscilatting between j = 1 and j = 2

// vector<int> twoSum(vector<int>& v, int target) {
// 	int i = 0, j = v.size() - 1;
// 	vector<int> result;
// 	int curr = INT_MIN;
// 	while (curr != target) {
// 		curr = v[i] + v[j];
// 		vector<int> neighbours = {i + 1, i - 1, j + 1, j - 1};
// 		vector<int> filteredNbrs, nbrValues;
// 		for (auto n : neighbours) {
// 			if (n >= 0 && n < v.size() && n != i && n != j) {
// 				filteredNbrs.push_back(n);
// 				nbrValues.push_back(v[n]);
// 			}
// 		}
// 		if (curr > target) {
// 			int min = min_element(nbrValues.begin(), nbrValues.end()) - nbrValues.begin();
// 			if (v[i] > v[j])
// 				i = filteredNbrs[min];
// 			else
// 				j = filteredNbrs[min];
// 		}
// 		else if (curr < target) {
// 			int max = max_element(nbrValues.begin(), nbrValues.end()) - nbrValues.begin();
// 			if (v[i] < v[j])
// 				i = filteredNbrs[max];
// 			else
// 				j = filteredNbrs[max];
// 		}
// 		else {
// 			result.push_back(i);
// 			result.push_back(j);
// 		}
// 	}
// 	return result;
// }

// Testcases:-

// Inputs:

// 8
// 10 7
// 2 5 5 11 0 1 7
// 9 7
// 2 7 11 15 0 3 6
// 6 5
// 3 2 4 0 1
// 6 5
// 3 3 0 3 3
// 0 0

// 0 1
// 0
// 0 10
// 1 2 3 4 5 6 7 8 9
// 0 7
// -1 0 1 2 -1 -4

// Outputs:

// 0 5 5
// 1 2 7
// __________
// 0 2 7
// 0 3 6
// __________
// 0 2 4
// 1 2 3
// __________
// 0 3 3
// __________
//
// __________
//
// __________
//
// __________
// -1 -1 2
// -1 0 1
// __________
