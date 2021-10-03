#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <climits>
std::vector<int> c;
std::vector<std::vector<int>> dp;
std::vector<std::vector<int>> stages;

void recursive(int i){
	if(stages[i].size() == 0){
		dp[i][0] = 0;
		dp[i][1] = c[i];
		dp[i][2] = c[i];
		return;
	}

	for(auto it = stages[i].begin(); it != stages[i].end(); it++){
		recursive(*it);
	}

	int kids_not_covered = 0;
	int kids_covered = 0;
	int min_diff = INT_MAX;
	for(auto it = stages[i].begin(); it != stages[i].end(); it++){
		kids_not_covered += dp[*it][0];
		kids_covered += dp[*it][1];
		min_diff = std::min(min_diff, dp[*it][2] - dp[*it][1]);
	}

	dp[i][2] = kids_not_covered + c[i];
	dp[i][1] = std::min(dp[i][2], kids_covered + min_diff);
	dp[i][0] = std::min(dp[i][1], kids_covered);

}


void testcase() {
	int n;
	std::cin >> n;
	stages = std::vector<std::vector<int>> (n);
	c = std::vector<int> (n);
	dp = std::vector<std::vector<int>> (n, std::vector<int> (3));
	for(int i = 1; i < n; i++){
		int k, l;
		std::cin >> k >> l;
		stages[k].push_back(l);
	}

	for(int i = 0; i < n; i++){
		std::cin >> c[i];
	}

	recursive(0);

	std::cout << dp[0][1] << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
