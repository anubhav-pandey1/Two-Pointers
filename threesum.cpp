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

vector<vector<int>> threeSum(vector<int>& v, int K) {
	vector<vector<int>> triplets;
	sort(v.begin(), v.end());
	for (int fix = 0; fix < v.size(); fix++) {
		int left = fix + 1, right = v.size() - 1;
		int target = K - v[fix];
		while (left < right) {
			while (v[left] == v[left + 1])
				left++;
			while (v[right] == v[right - 1])
				right--;
			if (v[left] + v[right] > target) {
				right--;
			}
			else if (v[left] + v[right] < target) {
				left++;
			}
			else {
				triplets.push_back({v[fix], v[left], v[right]});
				left--, right++;
			}
		}
		while (v[fix] == v[fix + 1])
			fix++;
	}
	return triplets;
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

// 4
// 10
// 4
// 2 5 5 11
// 9
// 4
// 2 7 11 15
// 6
// 3
// 3 2 4
// 6
// 2
// 3 3

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
